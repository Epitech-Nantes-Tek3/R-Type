/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** Client
*/

/// @file Client/ClientRoom.cpp

#include "ClientRoom.hpp"
#include "ActionQueueComponent.hpp"
#include "ControllerButtonInputComponent.hpp"
#include "ControllerJoystickInputComponent.hpp"
#include "DrawComponents.hpp"
#include "Error/Error.hpp"
#include "GameComponents/PlayerComponent.hpp"
#include "GameComponents/PositionComponent.hpp"
#include "GameEntityManipulation/CreateEntitiesFunctions/CreateAlliedProjectile.hpp"
#include "GameSharedResources/GameClock.hpp"
#include "GameSharedResources/Random.hpp"
#include "GameSystems/CollidableSystem.hpp"
#include "GameSystems/DeathLifeSystem.hpp"
#include "GameSystems/DeathSystem.hpp"
#include "GameSystems/DecreaseLifeTimeSystem.hpp"
#include "GameSystems/LifeTimeDeathSystem.hpp"
#include "GameSystems/MovementSystem.hpp"
#include "GameSystems/UpdateClockSystem.hpp"
#include "GraphicsFontResource.hpp"
#include "GraphicsRectangleComponent.hpp"
#include "InputManagement.hpp"
#include "KeyboardInputComponent.hpp"
#include "LayerLvL.hpp"
#include "MouseInputComponent.hpp"
#include "RenderWindowResource.hpp"
#include "Transisthor/TransisthorECSLogic/Both/Components/Networkable.hpp"
#include "Transisthor/TransisthorECSLogic/Client/Components/NetworkServer.hpp"
#include "Transisthor/TransisthorECSLogic/Client/Systems/SendNewlyCreatedToServer.hpp"
#include "Transisthor/TransisthorECSLogic/Client/Systems/SendToServer.hpp"

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

void ClientRoom::initEcsGameData(void)
{
    _initSharedResources();
    _initSystems();
    _initEntities();
}

void ClientRoom::startConnexionProtocol(void)
{
    _communicatorInstance.get()->startReceiverListening();
    _communicatorInstance.get()->sendDataToAClient(_serverEndpoint, nullptr, 0, 10);
}

void ClientRoom::protocol12Answer(CommunicatorMessage connexionResponse)
{
    _state = ClientState::IN_GAME;
    _worldInstance.get()->addEntity().addComponent<NetworkServer>(connexionResponse.message.clientInfo.getId());
    // std::vector<std::shared_ptr<Entity>> joined = _worldInstance.get()->joinEntities<Player>();
    // createNewAlliedProjectile(*_worldInstance.get(), *joined[0],
    //    NewlyCreated().generate_uuid(_worldInstance.get()->getResource<RandomDevice>().getRandomDevice(), 16));
}

void ClientRoom::startLobbyLoop(void)
{
    CommunicatorMessage connexionResponse;

    startConnexionProtocol();
    initEcsGameData();
    _state = ClientState::LOBBY;
    while (_state != ClientState::ENDED && _state != ClientState::UNDEFINED) {
        try {
            connexionResponse = _communicatorInstance.get()->getLastMessage();
            if (connexionResponse.message.type == 11) {
                std::cerr << "No places left inside the wanted room. Please retry later" << std::endl;
                return;
            }
            if (connexionResponse.message.type == 12)
                protocol12Answer(connexionResponse);
        } catch (NetworkError &error) {
        }
        if (_state == ClientState::IN_GAME)
            _worldInstance.get()->runSystems(); /// WILL BE IMPROVED IN PART TWO (THREAD + CLOCK)
    }
}

void ClientRoom::_initSharedResources()
{
    _worldInstance->addResource<RandomDevice>();
    _worldInstance->addResource<GameClock>();
    _worldInstance->addResource<RenderWindowResource>();
    _worldInstance->addResource<GraphicsFontResource>("assets/arial.ttf");
    _worldInstance->addResource<NetworkableIdGenerator>();
}

void ClientRoom::_initSystems()
{
    _worldInstance->addSystem<SendToServer>();
    _worldInstance->addSystem<SendNewlyCreatedToServer>();
    _worldInstance->addSystem<DeathSystem>();
    _worldInstance->addSystem<Movement>();
    _worldInstance->addSystem<UpdateClock>();
    _worldInstance->addSystem<DrawComponents>();
    _worldInstance->addSystem<InputManagement>();
}

void ClientRoom::_initEntities()
{
    _worldInstance->addEntity().addComponent<LayerLvL>().addComponent<GraphicsRectangleComponent>();
    _worldInstance->addEntity()
        .addComponent<MouseInputComponent>()
        .addComponent<KeyboardInputComponent>()
        .addComponent<ControllerButtonInputComponent>()
        .addComponent<ControllerJoystickInputComponent>()
        .addComponent<ActionQueueComponent>();
}