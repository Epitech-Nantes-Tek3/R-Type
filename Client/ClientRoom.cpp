/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** Client
*/

/// @file Client/ClientRoom.cpp

#include "ClientRoom.hpp"
#include <functional>
#include "ActionQueueComponent.hpp"
#include "AllowControllerComponent.hpp"
#include "AllowMouseAndKeyboardComponent.hpp"
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
#include "SFMLComponents/TextureName.hpp"
#include "SFMLResource/GraphicsTextureResource.hpp"
#include "SFMLSystems/SfRectangleFollowEntitySystem.hpp"
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

void ClientRoom::_initSpritesForEntities()
{
    _worldInstance->addResource<GraphicsTextureResource>(GraphicsTextureResource::ENEMY_STATIC,
        "assets/EpiSprite/BasicEnemySpriteSheet.gif", sf::Vector2f(0, 0), sf::Vector2f(34, 34));
    GraphicsTextureResource &spritesList = _worldInstance->getResource<GraphicsTextureResource>();

    spritesList.addTexture(GraphicsTextureResource::PLAYER_STATIC, "assets/EpiSprite/BasicPlayerSpriteSheet.gif",
        sf::Vector2f(500, 0), sf::Vector2f(34, 34));
    spritesList.addTexture(GraphicsTextureResource::PROJECTILE_ENEMY,
        "assets/EpiSprite/BasicEnemyProjectileSpriteSheet.gif", sf::Vector2f(0, 0), sf::Vector2f(20, 20));
    spritesList.addTexture(GraphicsTextureResource::PROJECTILE_ALLY,
        "assets/EpiSprite/BasicAlliedProjectileSpriteSheet.gif", sf::Vector2f(0, 0), sf::Vector2f(20, 20));
    spritesList.addTexture(GraphicsTextureResource::BACKGROUND_LAYER_3, "assets/Backgrounds/back.png",
        sf::Vector2f(0, 0), sf::Vector2f(1920, 1080));
    spritesList.addTexture(GraphicsTextureResource::BACKGROUND_LAYER_2, "assets/Backgrounds/far.png",
        sf::Vector2f(0, 0), sf::Vector2f(1920, 1080));
    spritesList.addTexture(GraphicsTextureResource::BACKGROUND_LAYER_1, "assets/Backgrounds/middle.png",
        sf::Vector2f(0, 0), sf::Vector2f(1920, 1080));
}

void ClientRoom::_initSharedResources()
{
    _worldInstance->addResource<RandomDevice>();
    _worldInstance->addResource<GameClock>();
    _worldInstance->addResource<RenderWindowResource>();
    _worldInstance->addResource<GraphicsFontResource>("assets/fonts/arial.ttf");
    _initSpritesForEntities();
}

void ClientRoom::_initSystems()
{
    _worldInstance->addSystem<DeathSystem>();
    _worldInstance->addSystem<UpdateClock>();
    _worldInstance->addSystem<DrawComponents>();
    _worldInstance->addSystem<InputManagement>();
    _worldInstance->addSystem<SendToServer>();
    _worldInstance->addSystem<SendNewlyCreatedToServer>();
    _worldInstance->addSystem<SfRectangleFollowEntitySystem>();
    _worldInstance->addSystem<UpdateClock>();
    // _worldInstance->addSystem<Movement>();
}

void ClientRoom::_initBackgroundEntities()
{
    _worldInstance->addEntity()
        .addComponent<GraphicsRectangleComponent>(0, 0, 1920, 1080)
        .addComponent<Position>(0, 0)
        .addComponent<Velocity>(30, 30)
        .addComponent<LayerLvL>(LayerLvL::layer_e::BACKGROUND)
        .addComponent<TextureName>(GraphicsTextureResource::BACKGROUND_LAYER_1);

    _worldInstance->addEntity()
        .addComponent<GraphicsRectangleComponent>(0, 0, 1920, 1080)
        .addComponent<Position>(0, 0)
        .addComponent<Velocity>(60, 60)
        .addComponent<LayerLvL>(LayerLvL::layer_e::BACKGROUND)
        .addComponent<TextureName>(GraphicsTextureResource::BACKGROUND_LAYER_2);

    _worldInstance->addEntity()
        .addComponent<GraphicsRectangleComponent>(0, 0, 1920, 1080)
        .addComponent<Position>(0, 0)
        .addComponent<Velocity>(100, 100)
        .addComponent<LayerLvL>(LayerLvL::layer_e::BACKGROUND)
        .addComponent<TextureName>(GraphicsTextureResource::BACKGROUND_LAYER_3);
}

void ClientRoom::_initEntities()
{
    _worldInstance->addEntity()
        .addComponent<MouseInputComponent>()
        .addComponent<KeyboardInputComponent>()
        .addComponent<ControllerButtonInputComponent>()
        .addComponent<ControllerJoystickInputComponent>()
        .addComponent<ActionQueueComponent>()
        .addComponent<AllowMouseAndKeyboardComponent>()
        .addComponent<AllowControllerComponent>();
    auto entities = _worldInstance->joinEntities<KeyboardInputComponent>();

    for (auto &it : entities) {
        it->getComponent<KeyboardInputComponent>().keyboardMapActions.emplace(
            std::make_pair<sf::Keyboard::Key, std::pair<ActionQueueComponent::inputAction_e, float>>(sf::Keyboard::Z,
                std::make_pair<ActionQueueComponent::inputAction_e, float>(ActionQueueComponent::MOVEY, -9)));
        it->getComponent<KeyboardInputComponent>().keyboardMapActions.emplace(
            std::make_pair<sf::Keyboard::Key, std::pair<ActionQueueComponent::inputAction_e, float>>(sf::Keyboard::S,
                std::make_pair<ActionQueueComponent::inputAction_e, float>(ActionQueueComponent::MOVEY, 9)));
        it->getComponent<KeyboardInputComponent>().keyboardMapActions.emplace(
            std::make_pair<sf::Keyboard::Key, std::pair<ActionQueueComponent::inputAction_e, float>>(sf::Keyboard::Q,
                std::make_pair<ActionQueueComponent::inputAction_e, float>(ActionQueueComponent::MOVEX, -9)));
        it->getComponent<KeyboardInputComponent>().keyboardMapActions.emplace(
            std::make_pair<sf::Keyboard::Key, std::pair<ActionQueueComponent::inputAction_e, float>>(sf::Keyboard::D,
                std::make_pair<ActionQueueComponent::inputAction_e, float>(ActionQueueComponent::MOVEX, 9)));
        it->getComponent<KeyboardInputComponent>().keyboardMapActions.emplace(
            std::make_pair<sf::Keyboard::Key, std::pair<ActionQueueComponent::inputAction_e, float>>(
                sf::Keyboard::Enter,
                std::make_pair<ActionQueueComponent::inputAction_e, float>(ActionQueueComponent::SHOOT, 0)));
        it->getComponent<ControllerJoystickInputComponent>().controllerJoystickMapActions.emplace(
            std::make_pair<unsigned int, std::pair<ActionQueueComponent::inputAction_e, float>>(
                1, std::make_pair<ActionQueueComponent::inputAction_e, float>(ActionQueueComponent::MOVEY, 0)));
    }
    _initBackgroundEntities();
}
