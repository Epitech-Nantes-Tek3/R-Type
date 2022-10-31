/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** Client
*/

/// @file Client/ClientRoom.cpp

#include "ClientRoom.hpp"
#include <csignal>
#include <functional>
#include <mutex>
#include "ButtonAction.hpp"
#include "Error/Error.hpp"
#include "GraphicECS/SFML/Components/ActionQueueComponent.hpp"
#include "GraphicECS/SFML/Components/AllowControllerComponent.hpp"
#include "GraphicECS/SFML/Components/AllowMouseAndKeyboardComponent.hpp"
#include "GraphicECS/SFML/Components/ControllerButtonInputComponent.hpp"
#include "GraphicECS/SFML/Components/ControllerJoystickInputComponent.hpp"
#include "GraphicECS/SFML/Components/GraphicsRectangleComponent.hpp"
#include "GraphicECS/SFML/Components/KeyboardInputComponent.hpp"
#include "GraphicECS/SFML/Components/MouseInputComponent.hpp"
#include "GraphicECS/SFML/Components/ParallaxComponent.hpp"
#include "GraphicECS/SFML/Components/TextureName.hpp"
#include "GraphicECS/SFML/Resources/GraphicsFontResource.hpp"
#include "GraphicECS/SFML/Resources/GraphicsTextureResource.hpp"
#include "GraphicECS/SFML/Resources/RenderWindowResource.hpp"
#include "GraphicECS/SFML/Systems/AnimationSystem.hpp"
#include "GraphicECS/SFML/Systems/DrawComponents.hpp"
#include "GraphicECS/SFML/Systems/InputManagement.hpp"
#include "GraphicECS/SFML/Systems/ParallaxSystem.hpp"
#include "GraphicECS/SFML/Systems/SfObjectFollowEntitySystem.hpp"
#include "Transisthor/TransisthorECSLogic/Both/Components/Networkable.hpp"
#include "Transisthor/TransisthorECSLogic/Client/Components/NetworkServer.hpp"
#include "Transisthor/TransisthorECSLogic/Client/Systems/SendNewlyCreatedToServer.hpp"
#include "Transisthor/TransisthorECSLogic/Client/Systems/SendToServer.hpp"
#include "R-TypeLogic/EntityManipulation/ButtonManipulation/SharedResources/ButtonActionMap.hpp"
#include "R-TypeLogic/EntityManipulation/ButtonManipulation/SharedResources/MenuStates.hpp"
#include "R-TypeLogic/EntityManipulation/CreateEntitiesFunctions/CreateButton.hpp"
#include "R-TypeLogic/Global/Components/LayerLvL.hpp"
#include "R-TypeLogic/Global/Components/PlayerComponent.hpp"
#include "R-TypeLogic/Global/Components/PositionComponent.hpp"
#include "R-TypeLogic/Global/SharedResources/GameClock.hpp"
#include "R-TypeLogic/Global/SharedResources/Random.hpp"
#include "R-TypeLogic/Global/Systems/DeathSystem.hpp"
#include "R-TypeLogic/Global/Systems/MovementSystem.hpp"
#include "R-TypeLogic/Global/Systems/NoAfkInMenuSystem.hpp"
#include "R-TypeLogic/Global/Systems/UpdateClockSystem.hpp"

using namespace error_lib;
using namespace communicator_lib;
using namespace client_data;
using namespace ecs;
using namespace graphicECS::SFML::Systems;
using namespace graphicECS::SFML::Components;

static ClientRoom::ClientState *clientRoomState(nullptr);

/// @brief Useful function called when a sigint received.
/// @param signum Value of the received signal
void signalCallbackHandler(int signum)
{
    (void)signum;
    std::cerr << "Client Room wanted to be closed." << std::endl;
    if (*clientRoomState == ClientRoom::UNDEFINED)
        throw SignalError(
            "A sigint have been catched while the game have not started.", "ClientRoom.cpp -> signalCallbackHandler");
    *clientRoomState = ClientRoom::ENDED;
}

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
    clientRoomState = &_state;
    _pseudo = "";
    _password = "";
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
    clientRoomState = &_state;
    _pseudo = "";
    _password = "";
}

void ClientRoom::initEcsGameData(void)
{
    _initSharedResources();
    _initSystems();
    _initEntities();
}

void ClientRoom::startConnexionProtocol(void)
{
    void *networkData = std::malloc(sizeof(char) * 10);

    if (networkData == nullptr)
        throw MallocError("Malloc failed.");
    std::memcpy(networkData, _pseudo.c_str(), sizeof(char) * 5);
    std::memcpy((void *)((char *)networkData + sizeof(char) * 5), _password.c_str(), sizeof(char) * 5);
    _communicatorInstance.get()->startReceiverListening();
    _communicatorInstance.get()->sendDataToAClient(_serverEndpoint, networkData, sizeof(char) * 10, 14);
}

void ClientRoom::protocol12Answer(CommunicatorMessage connexionResponse)
{
    _state = ClientState::IN_GAME;
    _worldInstance.get()->addEntity().addComponent<NetworkServer>(connexionResponse.message.clientInfo.getId());
    auto &clock = _worldInstance.get()->getResource<GameClock>();
    auto guard = std::lock_guard(clock);
    clock.resetClock();
    clock.resetClock();
}

void ClientRoom::_protocol15Answer(CommunicatorMessage connectionResponse)
{
    unsigned short roomNumber = 0;
    std::size_t offset = sizeof(unsigned short);

    std::memcpy(&roomNumber, connectionResponse.message.data, sizeof(unsigned short));
    std::cerr << "Succesfully connected to the hub." << std::endl;
    std::cerr << "Available Rooms : " << std::endl;
    for (int i = 0; i < roomNumber; i++) {
        unsigned short roomId = 0;
        std::memcpy(&roomId, (void *)((char *)connectionResponse.message.data + offset), sizeof(unsigned short));
        offset += sizeof(unsigned short);
        char *tempRoomName = (char *)connectionResponse.message.data + offset;
        std::string roomName(11, '\0');
        for (int j = 0; j < 10; j++)
            roomName[j] = tempRoomName[j];
        offset += sizeof(char) * 10;
        std::cerr << "\t" << roomId << " : " << roomName << " is available." << std::endl;
    }

    std::cerr << "If you want to join a existent room, please refer Y. Otherwise use N : ";
    char choosedMod = '\0';

    std::cin >> choosedMod;
    if (choosedMod == 'Y') {
        std::cerr << "Refer in the terminal the wanted room id : ";
        unsigned short choosenRoomId = 0;

        std::cin >> choosenRoomId; /// WILL BE REMOVED WHEN GRAPHICAL INTERACTION HAS BEEN IMPLEMENTED
        std::cerr << "Waiting for room number " << choosenRoomId << " answer..." << std::endl;
        void *networkData = std::malloc(sizeof(unsigned short));

        if (networkData == nullptr)
            throw std::logic_error("Malloc failed.");
        std::memcpy(networkData, &choosenRoomId, sizeof(unsigned short));
        _communicatorInstance.get()->sendDataToAClient(_serverEndpoint, networkData, sizeof(unsigned short), 16);
    } else if (choosedMod == 'N') {
        std::cerr << "Refer in the terminal the wanted room name : ";
        std::string roomName;

        std::cin >> roomName; /// WILL BE REMOVED WHEN GRAPHICAL INTERACTION HAS BEEN IMPLEMENTEND
        if (roomName.size() != 10) {
            std::cerr << "Please refer a valid room name (10 characters)." << std::endl;
            _state = ClientState::ENDED;
            return;
        }
        void *networkData = std::malloc(sizeof(char) * 10);

        if (networkData == nullptr)
            throw std::logic_error("Malloc failed.");
        std::memcpy(networkData, roomName.c_str(), sizeof(char) * 10);
        _communicatorInstance.get()->sendDataToAClient(_serverEndpoint, networkData, sizeof(char) * 10, 17);
    } else {
        std::cerr << "Not a valid option ;)" << std::endl;
        _state = ClientState::ENDED;
    }
}

void ClientRoom::_getClientPseudoAndPassword()
{
    std::string pseudo;
    std::string password;

    std::cerr << "Welcome to the R-Type game !" << std::endl;
    std::cerr << "If there is no player with your pseudonyme inside the database a new one will be created with the "
                 "given password."
              << std::endl;
    std::cerr << "Please refer your pseudonyme (5 characters): ";
    std::cin >> pseudo;
    if (pseudo.size() != 5) {
        std::cerr << "Nop ! Please enter a 5 characters pseudonyme.";
        _state = ClientState::ENDED;
        return;
    }
    std::cerr << "Welcome " << pseudo << ". Please now enter your password (5 characters): ";
    std::cin >> password;
    if (password.size() != 5) {
        std::cerr << "Nop ! Please enter a 5 characters password.";
        _state = ClientState::ENDED;
        return;
    }
    _pseudo = pseudo;
    _password = password;
}

void ClientRoom::_connectToARoom()
{
    void *networkData = std::malloc(sizeof(char) * 5);

    if (networkData == nullptr)
        throw MallocError("Malloc failed.");
    std::memcpy(networkData, _pseudo.c_str(), sizeof(char) * 5);
    _communicatorInstance.get()->sendDataToAClient(_serverEndpoint, networkData, sizeof(char) * 5, 10);
}

void ClientRoom::startLobbyLoop(void)
{
    CommunicatorMessage connectionOperation;

    std::signal(SIGINT, signalCallbackHandler);
    _getClientPseudoAndPassword();
    if (_state != ClientState::ENDED)
        startConnexionProtocol();
    while (_state != ClientState::ENDED && _state == ClientState::UNDEFINED) {
        try {
            connectionOperation = _communicatorInstance.get()->getLastMessage();
            if (connectionOperation.message.type == 11) {
                std::cerr << "No places left inside the hub. Please retry later" << std::endl;
                return;
            }
            if (connectionOperation.message.type == 15)
                _protocol15Answer(connectionOperation);
            if (connectionOperation.message.type == 20) {
                _serverEndpoint = _communicatorInstance->getClientByHisId(_communicatorInstance->getServerEndpointId());
                break;
            }
        } catch (NetworkError &error) {
        }
    }
    if (_state != ClientState::ENDED) {
        initEcsGameData();
        _connectToARoom();
        _state = ClientState::LOBBY;
    }
    while (_state != ClientState::ENDED && _state != ClientState::UNDEFINED) {
        try {
            connectionOperation = _communicatorInstance.get()->getLastMessage();
            if (connectionOperation.message.type == 11) {
                std::cerr << "No places left inside the wanted room. Please retry later" << std::endl;
                return;
            }
            if (connectionOperation.message.type == 12)
                protocol12Answer(connectionOperation);
            if (connectionOperation.message.type == 13)
                _holdADisconnectionRequest();
        } catch (NetworkError &error) {
        }
        if (_state == ClientState::IN_GAME) {
            _worldInstance.get()->runSystems(); /// WILL BE IMPROVED IN PART TWO (THREAD + CLOCK)
        }
    }
    _disconectionProcess();
}

void ClientRoom::_disconectionProcess()
{
    _communicatorInstance.get()->sendDataToAClient(_serverEndpoint, nullptr, 0, 13);
}

void ClientRoom::_holdADisconnectionRequest() { _state = ClientState::ENDED; }

void ClientRoom::_initSpritesForEntities()
{
    _worldInstance->addResource<GraphicsTextureResource>(GraphicsTextureResource::ENEMY_STATIC,
        "assets/EpiSprite/BasicEnemySpriteSheet.gif", sf::Vector2f(0, 0), sf::Vector2f(34, 34));
    GraphicsTextureResource &spritesList = _worldInstance->getResource<GraphicsTextureResource>();
    auto guard = std::lock_guard(spritesList);

    spritesList.addTexture(GraphicsTextureResource::PLAYER_STATIC_1, "assets/EpiSprite/BasicPlayerSpriteSheet.gif",
        sf::Vector2f(534 / 16 * 8, 0), sf::Vector2f(534 / 16, 34));
    spritesList.addTexture(GraphicsTextureResource::PLAYER_STATIC_2, "assets/EpiSprite/BasicPlayerSpriteSheet.gif",
        sf::Vector2f(534 / 16 * 9, 0), sf::Vector2f(534 / 16, 34));
    spritesList.addTexture(GraphicsTextureResource::PLAYER_STATIC_3, "assets/EpiSprite/BasicPlayerSpriteSheet.gif",
        sf::Vector2f(534 / 16 * 10, 0), sf::Vector2f(534 / 16, 34));
    spritesList.addTexture(GraphicsTextureResource::PLAYER_STATIC_4, "assets/EpiSprite/BasicPlayerSpriteSheet.gif",
        sf::Vector2f(534 / 16 * 11, 0), sf::Vector2f(534 / 16, 34));
    spritesList.addTexture(GraphicsTextureResource::PLAYER_STATIC_5, "assets/EpiSprite/BasicPlayerSpriteSheet.gif",
        sf::Vector2f(534 / 16 * 12, 0), sf::Vector2f(534 / 16, 34));
    spritesList.addTexture(GraphicsTextureResource::PLAYER_STATIC_6, "assets/EpiSprite/BasicPlayerSpriteSheet.gif",
        sf::Vector2f(534 / 16 * 13, 0), sf::Vector2f(534 / 16, 34));
    spritesList.addTexture(GraphicsTextureResource::PLAYER_STATIC_7, "assets/EpiSprite/BasicPlayerSpriteSheet.gif",
        sf::Vector2f(534 / 16 * 14, 0), sf::Vector2f(534 / 16, 34));
    spritesList.addTexture(GraphicsTextureResource::PLAYER_STATIC_8, "assets/EpiSprite/BasicPlayerSpriteSheet.gif",
        sf::Vector2f(534 / 16 * 15, 0), sf::Vector2f(534 / 16, 34));
    spritesList.addTexture(GraphicsTextureResource::PROJECTILE_ENEMY,
        "assets/EpiSprite/BasicEnemyProjectileSpriteSheet.gif", sf::Vector2f(0, 0), sf::Vector2f(34, 34));
    spritesList.addTexture(GraphicsTextureResource::PROJECTILE_ALLY,
        "assets/EpiSprite/BasicAlliedProjectileSpriteSheet.gif", sf::Vector2f(0, 0), sf::Vector2f(20, 20));
    spritesList.addTexture(GraphicsTextureResource::BACKGROUND_LAYER_3, "assets/Backgrounds/back.png",
        sf::Vector2f(0, 0), sf::Vector2f(1920, 1080));
    spritesList.addTexture(GraphicsTextureResource::BACKGROUND_LAYER_2, "assets/Backgrounds/far.png",
        sf::Vector2f(0, 0), sf::Vector2f(1920, 1080));
    spritesList.addTexture(GraphicsTextureResource::BACKGROUND_LAYER_1, "assets/Backgrounds/middle.png",
        sf::Vector2f(0, 0), sf::Vector2f(1920, 1080));
    spritesList.addTexture(GraphicsTextureResource::BUTTON, "assets/EpiSprite/r-typesheet11.gif", sf::Vector2f(34, 0),
        sf::Vector2f(34, 34));
}

void ClientRoom::_initSharedResources()
{
    _worldInstance->addResource<RandomDevice>();
    _worldInstance->addResource<GameClock>();
    _worldInstance->addResource<RenderWindowResource>();
    _worldInstance->addResource<GraphicsFontResource>("assets/fonts/arial.ttf");
    _worldInstance->addResource<MenuStates>(MenuStates::IN_GAME);
    _initSpritesForEntities();
}

void ClientRoom::_initSystems()
{
    _worldInstance->addSystem<UpdateClock>();
    _worldInstance->addSystem<DeathSystem>();
    _worldInstance->addSystem<DrawComponents>();
    _worldInstance->addSystem<InputManagement>();
    _worldInstance->addSystem<SendToServer>();
    _worldInstance->addSystem<SendNewlyCreatedToServer>();
    _worldInstance->addSystem<SfObjectFollowEntitySystem>();
    _worldInstance->addSystem<Parallax>();
    _worldInstance->addSystem<Movement>();
    _worldInstance->addSystem<AnimationSystem>();
    _worldInstance->addSystem<NoAfkInMenu>();
}

void ClientRoom::_initBackgroundEntities()
{
    size_t firstID = _worldInstance->addEntity()
                         .addComponent<ParallaxBackground>()
                         .addComponent<GraphicsRectangleComponent>(-1920, 0, 1920, 1080)
                         .addComponent<Position>(1920, 0)
                         .addComponent<Velocity>(-300, 0)
                         .addComponent<LayerLvL>(LayerLvL::layer_e::DECORATION)
                         .addComponent<TextureName>(GraphicsTextureResource::BACKGROUND_LAYER_1)
                         .getId();

    _worldInstance.get()->getEntity(firstID).getComponent<GraphicsRectangleComponent>().shape.setFillColor(
        sf::Color(0xA0A0A0ff));

    size_t secondID = _worldInstance->addEntity()
                          .addComponent<ParallaxBackground>()
                          .addComponent<GraphicsRectangleComponent>(0, 0, 1920, 1080)
                          .addComponent<Position>(0, 0)
                          .addComponent<Velocity>(-300, 0)
                          .addComponent<LayerLvL>(LayerLvL::layer_e::DECORATION)
                          .addComponent<TextureName>(GraphicsTextureResource::BACKGROUND_LAYER_1)
                          .getId();

    _worldInstance.get()->getEntity(secondID).getComponent<GraphicsRectangleComponent>().shape.setFillColor(
        sf::Color(0xA0A0A0ff));

    _worldInstance->addEntity()
        .addComponent<ParallaxBackground>()
        .addComponent<GraphicsRectangleComponent>(-1920, 0, 1920, 1080)
        .addComponent<Position>(1920, 0)
        .addComponent<Velocity>(-200, 0)
        .addComponent<LayerLvL>(LayerLvL::layer_e::MIDDLE)
        .addComponent<TextureName>(GraphicsTextureResource::BACKGROUND_LAYER_2);

    _worldInstance->addEntity()
        .addComponent<ParallaxBackground>()
        .addComponent<GraphicsRectangleComponent>(0, 0, 1920, 1080)
        .addComponent<Position>(0, 0)
        .addComponent<Velocity>(-200, 0)
        .addComponent<LayerLvL>(LayerLvL::layer_e::MIDDLE)
        .addComponent<TextureName>(GraphicsTextureResource::BACKGROUND_LAYER_2);

    _worldInstance->addEntity()
        .addComponent<ParallaxBackground>()
        .addComponent<GraphicsRectangleComponent>(-1920, 0, 1920, 1080)
        .addComponent<Position>(1920, 0)
        .addComponent<Velocity>(-100, 0)
        .addComponent<LayerLvL>(LayerLvL::layer_e::BACKGROUND)
        .addComponent<TextureName>(GraphicsTextureResource::BACKGROUND_LAYER_3);

    _worldInstance->addEntity()
        .addComponent<ParallaxBackground>()
        .addComponent<GraphicsRectangleComponent>(0, 0, 1920, 1080)
        .addComponent<Position>(0, 0)
        .addComponent<Velocity>(-100, 0)
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
                std::make_pair<ActionQueueComponent::inputAction_e, float>(ActionQueueComponent::MOVEY, -200)));
        it->getComponent<KeyboardInputComponent>().keyboardMapActions.emplace(
            std::make_pair<sf::Keyboard::Key, std::pair<ActionQueueComponent::inputAction_e, float>>(sf::Keyboard::S,
                std::make_pair<ActionQueueComponent::inputAction_e, float>(ActionQueueComponent::MOVEY, 200)));
        it->getComponent<KeyboardInputComponent>().keyboardMapActions.emplace(
            std::make_pair<sf::Keyboard::Key, std::pair<ActionQueueComponent::inputAction_e, float>>(sf::Keyboard::Q,
                std::make_pair<ActionQueueComponent::inputAction_e, float>(ActionQueueComponent::MOVEX, -200)));
        it->getComponent<KeyboardInputComponent>().keyboardMapActions.emplace(
            std::make_pair<sf::Keyboard::Key, std::pair<ActionQueueComponent::inputAction_e, float>>(sf::Keyboard::D,
                std::make_pair<ActionQueueComponent::inputAction_e, float>(ActionQueueComponent::MOVEX, 200)));
        it->getComponent<KeyboardInputComponent>().keyboardMapActions.emplace(
            std::make_pair<sf::Keyboard::Key, std::pair<ActionQueueComponent::inputAction_e, float>>(
                sf::Keyboard::Enter,
                std::make_pair<ActionQueueComponent::inputAction_e, float>(ActionQueueComponent::SHOOT, 10)));
        it->getComponent<ControllerJoystickInputComponent>().controllerJoystickMapActions.emplace(
            std::make_pair<unsigned int, std::pair<ActionQueueComponent::inputAction_e, float>>(
                1, std::make_pair<ActionQueueComponent::inputAction_e, float>(ActionQueueComponent::MOVEY, 0)));
        it->getComponent<MouseInputComponent>().MouseMapActions.emplace(
            std::make_pair<sf::Mouse::Button, std::pair<ActionQueueComponent::inputAction_e, float>>(
                sf::Mouse::Button::Left,
                std::make_pair<ActionQueueComponent::inputAction_e, float>(ActionQueueComponent::BUTTON_CLICK, 0)));
    }
    _initBackgroundEntities();
    _initButtons();
}

void ClientRoom::_initButtons()
{
    _worldInstance->addResource<ButtonActionMap>(ButtonActionMap::EXIT, std::function<void(World &)>(exitWindow));
    ButtonActionMap &actionsList = _worldInstance->getResource<ButtonActionMap>();
    actionsList.addAction(ButtonActionMap::RESUME, std::function<void(World &)>(resumeGame));
    actionsList.addAction(ButtonActionMap::PAUSE, std::function<void(World &)>(pauseGame));
    createNewButton(
        *(_worldInstance.get()), 0, 0, 68, 68, ButtonActionMap::PAUSE, LayerLvL::BUTTON, MenuStates::IN_GAME);
    createNewButton(*(_worldInstance.get()), 909, 200, 102, 102, ButtonActionMap::RESUME, LayerLvL::BUTTON,
        MenuStates::GAME_PAUSED);
    createNewButton(
        *(_worldInstance.get()), 909, 500, 102, 102, ButtonActionMap::EXIT, LayerLvL::BUTTON, MenuStates::GAME_PAUSED);
}
