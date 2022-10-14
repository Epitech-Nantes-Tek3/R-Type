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
#include "Transisthor/TransisthorECSLogic/Both/Components/Networkable.hpp"
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

/// @brief A useless system used for functional testing purpose
struct Temp : public System {
    void run(World &world) { (void)world; }
};

void Room::initEcsGameData(void)
{
    _worldInstance->addResource<NetworkableIdGenerator>();
    _worldInstance->addResource<RandomDevice>();
    _worldInstance->addSystem<Temp>();
    _worldInstance->addSystem<SendToClient>();
    _worldInstance->addSystem<SendNewlyCreatedToClients>();
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
    std::size_t playerId = createNewPlayer(*_worldInstance.get(), 10, 10, 0, 0, 1, 4, 4, 100, 10, 4, "",
        _worldInstance.get()
            ->getResource<NetworkableIdGenerator>()
            .generateNewNetworkableId()); /// CREATE A NEW ENTITY (INITIATED BY THE SERVER)
    std::size_t enemyId = createNewEnemyRandom(*_worldInstance.get(), 0, 0, 1, 4, 4, 100, 10, 5, "",
        _worldInstance.get()
            ->getResource<NetworkableIdGenerator>()
            .generateNewNetworkableId()); /// CREATE A NEW ENTITY (INITIATED BY THE SERVER)
    _worldInstance.get()->getEntity(playerId).addComponent<NetworkClient>(connexionDemand.message.clientInfo.getId());
    std::vector<std::shared_ptr<Entity>> joined = _worldInstance.get()->joinEntities<Networkable>();

    for (std::shared_ptr<Entity> entityPtr : joined) {
        if (entityPtr->contains<AlliedProjectile>()) {
            _worldInstance.get()->getTransisthorBridge()->transitEcsDataToNetworkDataEntityAlliedProjectile(
                entityPtr->getComponent<Networkable>().id, entityPtr->getComponent<AlliedProjectile>().parentNetworkId,
                "", {connexionDemand.message.clientInfo.getId()});
        }
        if (entityPtr->contains<Enemy>()) {
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
        if (entityPtr->contains<EnemyProjectile>()) {
            _worldInstance.get()->getTransisthorBridge()->transitEcsDataToNetworkDataEntityEnemyProjectile(
                entityPtr->getComponent<Networkable>().id, entityPtr->getComponent<AlliedProjectile>().parentNetworkId,
                "", {connexionDemand.message.clientInfo.getId()});
        }
        if (entityPtr->contains<Obstacle>()) {
            Position &pos = entityPtr->getComponent<Position>();

            _worldInstance.get()->getTransisthorBridge()->transitEcsDataToNetworkDataEntityObstacle(
                entityPtr->getComponent<Networkable>().id, pos.x, pos.y, entityPtr->getComponent<Damage>().damagePoint,
                "", {connexionDemand.message.clientInfo.getId()});
        }
        if (entityPtr->contains<Player>()) {
            Position &pos = entityPtr->getComponent<Position>();
            Velocity &vel = entityPtr->getComponent<Velocity>();
            Size &size = entityPtr->getComponent<Size>();
            if (playerId != entityPtr->getId()) {
                _worldInstance.get()->getTransisthorBridge()->transitEcsDataToNetworkDataEntityPlayer(
                    entityPtr->getComponent<Networkable>().id, pos.x, pos.y, vel.multiplierAbscissa,
                    vel.multiplierOrdinate, entityPtr->getComponent<Weight>().weight, size.x, size.y,
                    entityPtr->getComponent<Life>().lifePoint, entityPtr->getComponent<Damage>().damagePoint,
                    entityPtr->getComponent<DamageRadius>().radius, "", {connexionDemand.message.clientInfo.getId()});
            }
        }
        if (entityPtr->contains<Projectile>()) {
            Position &pos = entityPtr->getComponent<Position>();
            Velocity &vel = entityPtr->getComponent<Velocity>();

            _worldInstance.get()->getTransisthorBridge()->transitEcsDataToNetworkDataEntityProjectile(
                entityPtr->getComponent<Networkable>().id, pos.x, pos.y, vel.multiplierAbscissa, vel.multiplierOrdinate,
                entityPtr->getComponent<Damage>().damagePoint, "", {connexionDemand.message.clientInfo.getId()});
        }
    }
    _communicatorInstance.get()->sendDataToAClient(connexionDemand.message.clientInfo, nullptr, 0, 12);
}
