/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** Room
*/

/// @file Server/Room.cpp

#include "Room.hpp"
#include <csignal>
#include <mutex>
#include "Error/Error.hpp"
#include "Transisthor/TransisthorECSLogic/Both/Components/Networkable.hpp"
#include "Transisthor/TransisthorECSLogic/Both/Resources/SendingFrequency.hpp"
#include "Transisthor/TransisthorECSLogic/Server/Components/NetworkClient.hpp"
#include "Transisthor/TransisthorECSLogic/Server/Resources/NetworkableIdGenerator.hpp"
#include "Transisthor/TransisthorECSLogic/Server/Systems/SendNewlyCreatedToClients.hpp"
#include "Transisthor/TransisthorECSLogic/Server/Systems/SendToClient.hpp"
#include "R-TypeLogic/EntityManipulation/CreateEntitiesFunctions/CreateEnemy.hpp"
#include "R-TypeLogic/EntityManipulation/CreateEntitiesFunctions/CreatePlayer.hpp"
#include "R-TypeLogic/Global/Components/AlliedProjectileComponent.hpp"
#include "R-TypeLogic/Global/Components/DamageComponent.hpp"
#include "R-TypeLogic/Global/Components/DamageRadiusComponent.hpp"
#include "R-TypeLogic/Global/Components/DisconnectableComponent.hpp"
#include "R-TypeLogic/Global/Components/EnemyComponent.hpp"
#include "R-TypeLogic/Global/Components/EnemyProjectileComponent.hpp"
#include "R-TypeLogic/Global/Components/ObstacleComponent.hpp"
#include "R-TypeLogic/Global/Components/PositionComponent.hpp"
#include "R-TypeLogic/Global/Components/ProjectileComponent.hpp"
#include "R-TypeLogic/Global/SharedResources/GameClock.hpp"
#include "R-TypeLogic/Global/Systems/DeathSystem.hpp"
#include "R-TypeLogic/Global/Systems/MovementSystem.hpp"
#include "R-TypeLogic/Global/Systems/UpdateClockSystem.hpp"
#include "R-TypeLogic/Server/Systems/CollidableSystem.hpp"
#include "R-TypeLogic/Server/Systems/DeathLifeSystem.hpp"
#include "R-TypeLogic/Server/Systems/DecreaseLifeTimeSystem.hpp"
#include "R-TypeLogic/Server/Systems/DisconnectableSystem.hpp"
#include "R-TypeLogic/Server/Systems/EnemiesGoRandom.hpp"
#include "R-TypeLogic/Server/Systems/EnemyShootSystem.hpp"
#include "R-TypeLogic/Server/Systems/LifeTimeDeathSystem.hpp"
#include "R-TypeLogic/Server/Systems/RemoveAfkSystem.hpp"

using namespace server_data;
using namespace error_lib;
using namespace communicator_lib;
using namespace ecs;

static server_data::Room::RoomState roomState(Room::RoomState::UNDEFINED);

/// @brief Useful function called when a sigint received.
/// @param signum Value of the received signal
void signalCallbackHandler(int signum)
{
    (void)signum;
    std::cerr << "Room ask to be closed." << std::endl;
    roomState = Room::ENDED;
}

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
    _name = std::string(10, '\0');
}

Room::Room(unsigned short id, std::string name, Client networkInformations)
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
    _name = name;
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
    _worldInstance->addSystem<Collide>();
    _worldInstance->addSystem<DeathLife>();
    _worldInstance->addSystem<DeathSystem>();
    _worldInstance->addSystem<LifeTimeDeath>();
    _worldInstance->addSystem<DecreaseLifeTime>();
    _worldInstance->addSystem<DisconnectableSystem>();
    _worldInstance->addSystem<RemoveAfkSystem>();
}

void Room::startConnexionProtocol(void) { _communicatorInstance.get()->startReceiverListening(); }

void Room::startLobbyLoop(void)
{
    CommunicatorMessage connectionOperation;

    std::signal(SIGINT, signalCallbackHandler);
    std::cerr << "1" << std::endl;
    startConnexionProtocol();
    std::cerr << "2" << std::endl;
    initEcsGameData();
    std::cerr << "3" << std::endl;
    _state = RoomState::LOBBY;
    while (_state != RoomState::ENDED && _state != RoomState::UNDEFINED && roomState != RoomState::ENDED) {
        //std::cerr << "3.1" << std::endl;
        try {
            connectionOperation = _communicatorInstance.get()->getLastMessage();
            if (connectionOperation.message.type == 10)
                holdANewConnexionRequest(connectionOperation);
            if (connectionOperation.message.type == 13)
                _holdADisconnectionRequest(connectionOperation);
        } catch (NetworkError &error) {
        }
        if (_state == RoomState::IN_GAME) {
            std::cerr << "3.2" << std::endl;
            _worldInstance.get()->runSystems();
        } /// WILL BE IMPROVED IN PART TWO (THREAD + CLOCK)
        //std::cerr << "3.3" << std::endl;
        _activePlayerGestion();
    }
    std::cerr << "4" << std::endl;
    _disconectionProcess();
    std::cerr << "5" << std::endl;
}

void Room::_disconectionProcess()
{
    auto clientList = _communicatorInstance.get()->getClientList();

    for (auto it : clientList)
        _communicatorInstance.get()->sendDataToAClient(it, nullptr, 0, 13);
}

void Room::_holdADisconnectionRequest(CommunicatorMessage disconnectionDemand)
{
    Client &client = _communicatorInstance->getClientFromList(
        disconnectionDemand.message.clientInfo.getAddress(), disconnectionDemand.message.clientInfo.getPort());
    size_t clientId = 0;

    try {
        clientId = getEntityPlayerByHisNetworkId(client.getId());
    } catch (EcsError &error) {
        (void)error;
        return;
    }
    _worldInstance->getEntity(clientId).addComponent<Disconnectable>();
    std::cerr << "Player succesfully disconnected." << std::endl;
}

void Room::_activePlayerGestion()
{
    std::vector<std::shared_ptr<ecs::Entity>> joined = _worldInstance->joinEntities<Player>();
    size_t activePlayer = joined.size();

    if (activePlayer != 0)
        return;
    if (_remainingPlaces == 0)
        _state = RoomState::ENDED;
    else
        _state = RoomState::LOBBY;
}

size_t Room::getEntityPlayerByHisNetworkId(unsigned short networkId)
{
    std::vector<std::shared_ptr<ecs::Entity>> joined = _worldInstance->joinEntities<NetworkClient>();
    size_t temporary = 0;

    auto crossAllPlayer = [&networkId, &temporary](std::shared_ptr<ecs::Entity> entityPtr) {
        if (entityPtr->getComponent<NetworkClient>().id == networkId)
            temporary = entityPtr->getId();
    };
    std::for_each(joined.begin(), joined.end(), crossAllPlayer);
    if (temporary == 0)
        throw EcsError("No matching player founded.", "World.cpp -> getEntityPlayerByHisNetworkId");
    return temporary;
}

void Room::holdANewConnexionRequest(CommunicatorMessage connexionDemand)
{
    if (_remainingPlaces == 0) {
        _communicatorInstance.get()->sendDataToAClient(connexionDemand.message.clientInfo, nullptr, 0, 11);
        return;
    }
    _remainingPlaces -= 1;
    _state = RoomState::IN_GAME;
    std::cerr << "Room " << _id << " received a connexion protocol." << std::endl;
    NetworkableIdGenerator &generator = _worldInstance->getResource<NetworkableIdGenerator>();
    auto guard = std::lock_guard(generator);
    std::size_t playerId = createNewPlayer(*_worldInstance.get(), 20, 500, 0, 0, 1, 102, 102, 100, 10, 4, false,
        _remainingPlaces + 1, "", generator.generateNewNetworkableId());
    std::size_t enemyId = createNewEnemyRandom(
        *_worldInstance.get(), 0, 0, 1, 85, 85, 50, 10, 5, "", generator.generateNewNetworkableId());
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
        auto guard = std::lock_guard(*entityPtr.get());
        Position &pos = entityPtr->getComponent<Position>();
        Velocity &vel = entityPtr->getComponent<Velocity>();
        Size &size = entityPtr->getComponent<Size>();

        if (playerId != entityPtr->getId()) {
            std::free(_worldInstance.get()->getTransisthorBridge()->transitEcsDataToNetworkDataEntityPlayer(
                entityPtr->getComponent<Networkable>().id, pos.x, pos.y, vel.multiplierAbscissa, vel.multiplierOrdinate,
                entityPtr->getComponent<Weight>().weight, size.x, size.y, entityPtr->getComponent<Life>().lifePoint,
                entityPtr->getComponent<Damage>().damagePoint, entityPtr->getComponent<DamageRadius>().radius, false,
                entityPtr->getComponent<Player>().playerIdentifier, "", {connexionDemand.message.clientInfo.getId()}));
        } else {
            std::free(_worldInstance.get()->getTransisthorBridge()->transitEcsDataToNetworkDataEntityPlayer(
                entityPtr->getComponent<Networkable>().id, pos.x, pos.y, vel.multiplierAbscissa, vel.multiplierOrdinate,
                entityPtr->getComponent<Weight>().weight, size.x, size.y, entityPtr->getComponent<Life>().lifePoint,
                entityPtr->getComponent<Damage>().damagePoint, entityPtr->getComponent<DamageRadius>().radius, true,
                entityPtr->getComponent<Player>().playerIdentifier, "", {connexionDemand.message.clientInfo.getId()}));
            std::free(_worldInstance.get()->getTransisthorBridge()->transitEcsDataToNetworkDataEntityPlayer(
                entityPtr->getComponent<Networkable>().id, pos.x, pos.y, vel.multiplierAbscissa, vel.multiplierOrdinate,
                entityPtr->getComponent<Weight>().weight, size.x, size.y, entityPtr->getComponent<Life>().lifePoint,
                entityPtr->getComponent<Damage>().damagePoint, entityPtr->getComponent<DamageRadius>().radius, false,
                entityPtr->getComponent<Player>().playerIdentifier, "", clientIdList));
            entityPtr->getComponent<NewlyCreated>().sended = true;
        }
    }
    for (std::shared_ptr<Entity> entityPtr : enemies) {
        auto guard = std::lock_guard(*entityPtr.get());
        Position &pos = entityPtr->getComponent<Position>();
        Velocity &vel = entityPtr->getComponent<Velocity>();
        Size &size = entityPtr->getComponent<Size>();

        if (enemyId != entityPtr->getId()) {
            std::free(_worldInstance.get()->getTransisthorBridge()->transitEcsDataToNetworkDataEntityEnemy(
                entityPtr->getComponent<Networkable>().id, pos.x, pos.y, vel.multiplierAbscissa, vel.multiplierOrdinate,
                entityPtr->getComponent<Weight>().weight, size.x, size.y, entityPtr->getComponent<Life>().lifePoint,
                entityPtr->getComponent<Damage>().damagePoint, entityPtr->getComponent<DamageRadius>().radius, "",
                {connexionDemand.message.clientInfo.getId()}));
        }
    }
    for (std::shared_ptr<Entity> entityPtr : obstacles) {
        auto guard = std::lock_guard(*entityPtr.get());
        Position &pos = entityPtr->getComponent<Position>();

        std::free(_worldInstance.get()->getTransisthorBridge()->transitEcsDataToNetworkDataEntityObstacle(
            entityPtr->getComponent<Networkable>().id, pos.x, pos.y, entityPtr->getComponent<Damage>().damagePoint, "",
            {connexionDemand.message.clientInfo.getId()}));
    }
    for (std::shared_ptr<Entity> entityPtr : projectiles) {
        auto guard = std::lock_guard(*entityPtr.get());
        Position &pos = entityPtr->getComponent<Position>();
        Velocity &vel = entityPtr->getComponent<Velocity>();

        std::free(_worldInstance.get()->getTransisthorBridge()->transitEcsDataToNetworkDataEntityProjectile(
            entityPtr->getComponent<Networkable>().id, pos.x, pos.y, vel.multiplierAbscissa, vel.multiplierOrdinate,
            entityPtr->getComponent<Damage>().damagePoint, "", {connexionDemand.message.clientInfo.getId()}));
    }
    for (std::shared_ptr<Entity> entityPtr : alliedProjectiles) {
        auto guard = std::lock_guard(*entityPtr.get());
        std::free(_worldInstance.get()->getTransisthorBridge()->transitEcsDataToNetworkDataEntityAlliedProjectile(
            entityPtr->getComponent<Networkable>().id, entityPtr->getComponent<AlliedProjectile>().parentNetworkId, "",
            {connexionDemand.message.clientInfo.getId()}));
    }
    for (std::shared_ptr<Entity> entityPtr : enemyProjectiles) {
        auto guard = std::lock_guard(*entityPtr.get());
        std::free(_worldInstance.get()->getTransisthorBridge()->transitEcsDataToNetworkDataEntityEnemyProjectile(
            entityPtr->getComponent<Networkable>().id, entityPtr->getComponent<EnemyProjectile>().parentNetworkId, "",
            {connexionDemand.message.clientInfo.getId()}));
    }
    _communicatorInstance.get()->sendDataToAClient(connexionDemand.message.clientInfo, nullptr, 0, 12);
    if (_remainingPlaces == 3) {
        GameClock &clock = _worldInstance->getResource<GameClock>();
        auto guard = std::lock_guard(clock);
        clock.resetClock();
        clock.resetClock();
    }
}
