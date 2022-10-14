/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** Client
*/

/// @file Client/ClientRoom.cpp

#include "ClientRoom.hpp"
#include "Error/Error.hpp"
#include "GameComponents/PositionComponent.hpp"
#include "GameEntityManipulation/CreateEntitiesFunctions/CreateObstacle.hpp"
#include "Transisthor/TransisthorECSLogic/Both/Components/Networkable.hpp"
#include "GameClock.hpp"
#include "Random.hpp"
#include "RenderWindowResource.hpp"
#include "GraphicsFontResource.hpp"
#include "CollidableSystem.hpp"
#include "DeathLifeSystem.hpp"
#include "DeathSystem.hpp"
#include "DecreaseLifeTimeSystem.hpp"
#include "LifeTimeDeathSystem.hpp"
#include "MovementSystem.hpp"
#include "UpdateClockSystem.hpp"

using namespace error_lib;
using namespace communicator_lib;
using namespace client_data;
using namespace ecs;

ClientRoom::ClientRoom()
{
    _networkInformations = Client();
    _serverEndpoint = Client();
    _communicatorInstance = std::make_shared<Communicator>(_networkInformations);
    _worldInstance = std::make_shared<World>(1);
    _initSharedResources();
    _initSystems();
    _transisthorInstance = std::make_shared<Transisthor>(*(_communicatorInstance.get()), *(_worldInstance.get()));
    _communicatorInstance.get()->setTransisthorBridge(_transisthorInstance);
    _worldInstance.get()->setTransisthorBridge(_communicatorInstance.get()->getTransisthorBridge());
    _state = ClientState::UNDEFINED;
}

ClientRoom::ClientRoom(std::string address, unsigned short port, std::string serverAddress, unsigned short serverPort)
{
    _networkInformations = Client(address, port);
    _serverEndpoint = Client(serverAddress, serverPort);
    _communicatorInstance = std::make_shared<Communicator>(_networkInformations);
    _worldInstance = std::make_shared<World>(1);
    _transisthorInstance = std::make_shared<Transisthor>(*(_communicatorInstance.get()), *(_worldInstance.get()));
    _communicatorInstance.get()->setTransisthorBridge(_transisthorInstance);
    _worldInstance.get()->setTransisthorBridge(_communicatorInstance.get()->getTransisthorBridge());
    _state = ClientState::UNDEFINED;
}

void ClientRoom::startLobbyLoop(void)
{
    CommunicatorMessage connexionResponse;

    std::size_t entityId = createNewObstacle(*(_worldInstance.get()), 5, 60, 5);

    _worldInstance.get()->getEntity(entityId).addComponent<Networkable>(10);

    _communicatorInstance.get()->startReceiverListening();
    _communicatorInstance.get()->sendDataToAClient(_serverEndpoint, nullptr, 0, 10);
    _state = ClientState::LOBBY;
    while (_state != ClientState::ENDED && _state != ClientState::UNDEFINED) {
        try {
            Position entityPosition = _worldInstance.get()->getEntity(entityId).getComponent<Position>();
            std::cerr << "OBSTACLE POSITION : " << entityPosition.x << " , " << entityPosition.y << std::endl;
            connexionResponse = _communicatorInstance.get()->getLastMessage();
            std::cerr << "ClientRoom received a connexion protocol answer."
                      << std::endl; /// WILL BE DELETED WITH CONNEXION PROTOCOL ISSUE
        } catch (NetworkError &error) {
        }
        _worldInstance.get()->runSystems(); /// WILL BE IMPROVED IN PART TWO (THREAD + CLOCK)
    }
}

void ClientRoom::_initSharedResources()
{
    _worldInstance->addResource<GameClock>();
    _worldInstance->addResource<RandomDevice>();
    _worldInstance->addResource<RenderWindowResource>();
    _worldInstance->addResource<GraphicsFontResource>("assets/arial.ttf");
}

void ClientRoom::_initSystems()
{
    _worldInstance->addSystem<Collide>();
    _worldInstance->addSystem<DeathLife>();
    _worldInstance->addSystem<DeathSystem>();
    _worldInstance->addSystem<DecreaseLifeTime>();
    _worldInstance->addSystem<LifeTimeDeath>();
    _worldInstance->addSystem<Movement>();
    _worldInstance->addSystem<UpdateClock>();
}
