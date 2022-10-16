/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** Room
*/

/// @file Server/Room.cpp

#include "Room.hpp"
#include "Error/Error.hpp"
#include "GameComponents/AlliedProjectileComponent.hpp"
#include "GameComponents/DamageComponent.hpp"
#include "GameComponents/DamageRadiusComponent.hpp"
#include "GameComponents/EnemyComponent.hpp"
#include "GameComponents/EnemyProjectileComponent.hpp"
#include "GameComponents/ObstacleComponent.hpp"
#include "GameComponents/PositionComponent.hpp"
#include "GameComponents/ProjectileComponent.hpp"
#include "GameEntityManipulation/CreateEntitiesFunctions/CreateEnemy.hpp"
#include "GameEntityManipulation/CreateEntitiesFunctions/CreatePlayer.hpp"
#include "GameSharedResources/GameClock.hpp"
#include "GameSystems/CollidableSystem.hpp"
#include "GameSystems/DeathLifeSystem.hpp"
#include "GameSystems/DeathSystem.hpp"
#include "GameSystems/EnemiesGoRandom.hpp"
#include "GameSystems/EnemyShootSystem.hpp"
#include "GameSystems/LifeTimeDeathSystem.hpp"
#include "GameSystems/MovementSystem.hpp"
#include "GameSystems/UpdateClockSystem.hpp"
#include "Transisthor/TransisthorECSLogic/Both/Components/Networkable.hpp"
#include "Transisthor/TransisthorECSLogic/Both/Resources/SendingFrequency.hpp"
#include "Transisthor/TransisthorECSLogic/Server/Components/NetworkClient.hpp"
#include "Transisthor/TransisthorECSLogic/Server/Resources/NetworkableIdGenerator.hpp"
#include "Transisthor/TransisthorECSLogic/Server/Systems/SendNewlyCreatedToClients.hpp"
#include "Transisthor/TransisthorECSLogic/Server/Systems/SendToClient.hpp"

using namespace server_data;
using namespace error_lib;
using namespace communicator_lib;
using namespace ecs;

Room::Room()
{
    _id = 0;
    _networkInformations = Client();
    _communicatorInstance = std::make_shared<Communicator>(_networkInformations);
    _worldInstance = std::make_shared<World>(1);
    _transisthorInstance = std::make_shared<Transisthor>(*(_communicatorInstance.get()), *(_worldInstance.get()));
    _communicatorInstance.get()->setTransisthorBridge(_transisthorInstance);
    _worldInstance.get()->setTransisthorBridge(_communicatorInstance.get()->getTransisthorBridge());
    _state = RoomState::UNDEFINED;
    _remainingPlaces = 4;
}

Room::Room(unsigned short id, Client networkInformations)
{
    _id = id;
    _networkInformations = networkInformations;
    _communicatorInstance = std::make_shared<Communicator>(_networkInformations);
    _worldInstance = std::make_shared<World>(1);
    _transisthorInstance = std::make_shared<Transisthor>(*(_communicatorInstance.get()), *(_worldInstance.get()));
    _communicatorInstance.get()->setTransisthorBridge(_transisthorInstance);
    _worldInstance.get()->setTransisthorBridge(_communicatorInstance.get()->getTransisthorBridge());
    _state = RoomState::UNDEFINED;
    _remainingPlaces = 4;
}

void Room::initEcsGameData(void)
{
    _worldInstance->addSystem<UpdateClock>();
    _worldInstance->addResource<NetworkableIdGenerator>();
    _worldInstance->addResource<RandomDevice>();
    _worldInstance->addResource<GameClock>();
    _worldInstance->addResource<SendingFrequency>();
    _worldInstance->addSystem<SendToClient>();
    _worldInstance->addSystem<SendNewlyCreatedToClients>();
    _worldInstance->addSystem<Movement>();
    _worldInstance->addSystem<EnemiesGoRandom>();
    _worldInstance->addSystem<EnemyShootSystem>();
    //_worldInstance->addSystem<Collide>();
    //_worldInstance->addSystem<DeathLife>();
    //_worldInstance->addSystem<DeathSystem>();
    //_worldInstance->addSystem<LifeTimeDeath>();
}

void Room::startConnexionProtocol(void) { _communicatorInstance.get()->startReceiverListening(); }

void Room::startLobbyLoop(void)
{
    CommunicatorMessage connexionDemand;

    startConnexionProtocol();
    initEcsGameData();
    _state = RoomState::LOBBY;
    while (_state != RoomState::ENDED && _state != RoomState::UNDEFINED) {
        try {
            connexionDemand = _communicatorInstance.get()->getLastMessage();
            if (connexionDemand.message.type == 10)
                holdANewConnexionRequest(connexionDemand);
        } catch (NetworkError &error) {
        }
        if (_remainingPlaces != 4)
            _worldInstance.get()->runSystems(); /// WILL BE IMPROVED IN PART TWO (THREAD + CLOCK)
    }
}

void Room::holdANewConnexionRequest(CommunicatorMessage connexionDemand)
{
    if (_remainingPlaces == 0) {
        _communicatorInstance.get()->sendDataToAClient(connexionDemand.message.clientInfo, nullptr, 0, 11);
        return;
    }
    _remainingPlaces -= 1;
    std::cerr << "Room " << _id << " received a connexion protocol." << std::endl;
    std::size_t playerId = createNewPlayer(*_worldInstance.get(), 20, 500, 0, 0, 1, 102, 102, 100, 10, 4, false, "",
        _worldInstance->getResource<NetworkableIdGenerator>().generateNewNetworkableId());
    std::size_t enemyId = createNewEnemyRandom(*_worldInstance.get(), 0, 0, 1, 85, 85, 50, 10, 5, "",
        _worldInstance.get()->getResource<NetworkableIdGenerator>().generateNewNetworkableId());
    std::vector<std::shared_ptr<ecs::Entity>> clients = _worldInstance.get()->joinEntities<ecs::NetworkClient>();
    std::vector<unsigned short> clientIdList;
    auto addToClientList = [&clientIdList](std::shared_ptr<ecs::Entity> entityPtr) {
        clientIdList.emplace_back(entityPtr.get()->getComponent<ecs::NetworkClient>().id);
    };
    std::for_each(clients.begin(), clients.end(), addToClientList);
    _worldInstance.get()->getEntity(playerId).addComponent<NetworkClient>(connexionDemand.message.clientInfo.getId());
    std::vector<std::shared_ptr<Entity>> alliedProjectiles =
        _worldInstance.get()->joinEntities<Networkable, AlliedProjectile>();
    std::vector<std::shared_ptr<Entity>> enemies = _worldInstance.get()->joinEntities<Networkable, Enemy>();
    std::vector<std::shared_ptr<Entity>> enemyProjectiles =
        _worldInstance.get()->joinEntities<Networkable, EnemyProjectile>();
    std::vector<std::shared_ptr<Entity>> obstacles = _worldInstance.get()->joinEntities<Networkable, Obstacle>();
    std::vector<std::shared_ptr<Entity>> players = _worldInstance.get()->joinEntities<Networkable, Player>();
    std::vector<std::shared_ptr<Entity>> projectiles = _worldInstance.get()->joinEntities<Networkable, Projectile>();

    for (std::shared_ptr<Entity> entityPtr : players) {
        Position &pos = entityPtr->getComponent<Position>();
        Velocity &vel = entityPtr->getComponent<Velocity>();
        Size &size = entityPtr->getComponent<Size>();

        if (playerId != entityPtr->getId()) {
            _worldInstance.get()->getTransisthorBridge()->transitEcsDataToNetworkDataEntityPlayer(
                entityPtr->getComponent<Networkable>().id, pos.x, pos.y, vel.multiplierAbscissa, vel.multiplierOrdinate,
                entityPtr->getComponent<Weight>().weight, size.x, size.y, entityPtr->getComponent<Life>().lifePoint,
                entityPtr->getComponent<Damage>().damagePoint, entityPtr->getComponent<DamageRadius>().radius, false,
                "", {connexionDemand.message.clientInfo.getId()});
        } else {
            _worldInstance.get()->getTransisthorBridge()->transitEcsDataToNetworkDataEntityPlayer(
                entityPtr->getComponent<Networkable>().id, pos.x, pos.y, vel.multiplierAbscissa, vel.multiplierOrdinate,
                entityPtr->getComponent<Weight>().weight, size.x, size.y, entityPtr->getComponent<Life>().lifePoint,
                entityPtr->getComponent<Damage>().damagePoint, entityPtr->getComponent<DamageRadius>().radius, true, "",
                {connexionDemand.message.clientInfo.getId()});
            _worldInstance.get()->getTransisthorBridge()->transitEcsDataToNetworkDataEntityPlayer(
                entityPtr->getComponent<Networkable>().id, pos.x, pos.y, vel.multiplierAbscissa, vel.multiplierOrdinate,
                entityPtr->getComponent<Weight>().weight, size.x, size.y, entityPtr->getComponent<Life>().lifePoint,
                entityPtr->getComponent<Damage>().damagePoint, entityPtr->getComponent<DamageRadius>().radius, false,
                "", clientIdList);
            entityPtr->getComponent<NewlyCreated>().sended = true;
        }
    }
    for (std::shared_ptr<Entity> entityPtr : enemies) {
        Position &pos = entityPtr->getComponent<Position>();
        Velocity &vel = entityPtr->getComponent<Velocity>();
        Size &size = entityPtr->getComponent<Size>();

        if (enemyId != entityPtr->getId()) {
            _worldInstance.get()->getTransisthorBridge()->transitEcsDataToNetworkDataEntityEnemy(
                entityPtr->getComponent<Networkable>().id, pos.x, pos.y, vel.multiplierAbscissa, vel.multiplierOrdinate,
                entityPtr->getComponent<Weight>().weight, size.x, size.y, entityPtr->getComponent<Life>().lifePoint,
                entityPtr->getComponent<Damage>().damagePoint, entityPtr->getComponent<DamageRadius>().radius, "",
                {connexionDemand.message.clientInfo.getId()});
        }
    }
    for (std::shared_ptr<Entity> entityPtr : obstacles) {
        Position &pos = entityPtr->getComponent<Position>();

        _worldInstance.get()->getTransisthorBridge()->transitEcsDataToNetworkDataEntityObstacle(
            entityPtr->getComponent<Networkable>().id, pos.x, pos.y, entityPtr->getComponent<Damage>().damagePoint, "",
            {connexionDemand.message.clientInfo.getId()});
    }
    for (std::shared_ptr<Entity> entityPtr : projectiles) {
        Position &pos = entityPtr->getComponent<Position>();
        Velocity &vel = entityPtr->getComponent<Velocity>();

        _worldInstance.get()->getTransisthorBridge()->transitEcsDataToNetworkDataEntityProjectile(
            entityPtr->getComponent<Networkable>().id, pos.x, pos.y, vel.multiplierAbscissa, vel.multiplierOrdinate,
            entityPtr->getComponent<Damage>().damagePoint, "", {connexionDemand.message.clientInfo.getId()});
    }
    for (std::shared_ptr<Entity> entityPtr : alliedProjectiles) {
        _worldInstance.get()->getTransisthorBridge()->transitEcsDataToNetworkDataEntityAlliedProjectile(
            entityPtr->getComponent<Networkable>().id, entityPtr->getComponent<AlliedProjectile>().parentNetworkId, "",
            {connexionDemand.message.clientInfo.getId()});
    }
    for (std::shared_ptr<Entity> entityPtr : enemyProjectiles) {
        _worldInstance.get()->getTransisthorBridge()->transitEcsDataToNetworkDataEntityEnemyProjectile(
            entityPtr->getComponent<Networkable>().id, entityPtr->getComponent<EnemyProjectile>().parentNetworkId, "",
            {connexionDemand.message.clientInfo.getId()});
    }
    _communicatorInstance.get()->sendDataToAClient(connexionDemand.message.clientInfo, nullptr, 0, 12);
    if (_remainingPlaces == 3) {
        _worldInstance.get()->getResource<GameClock>().resetClock();
        _worldInstance.get()->getResource<GameClock>().resetClock();
    }
}
