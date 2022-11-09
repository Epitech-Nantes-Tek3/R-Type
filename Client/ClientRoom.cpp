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
#include "GraphicECS/SFML/Components/ChatMessageComponent.hpp"
#include "GraphicECS/SFML/Components/ControllerButtonInputComponent.hpp"
#include "GraphicECS/SFML/Components/ControllerJoystickInputComponent.hpp"
#include "GraphicECS/SFML/Components/GraphicsRectangleComponent.hpp"
#include "GraphicECS/SFML/Components/KeyboardInputComponent.hpp"
#include "GraphicECS/SFML/Components/MouseInputComponent.hpp"
#include "GraphicECS/SFML/Components/MusicComponent.hpp"
#include "GraphicECS/SFML/Components/ParallaxComponent.hpp"
#include "GraphicECS/SFML/Components/SoundComponent.hpp"
#include "GraphicECS/SFML/Components/TextureName.hpp"
#include "GraphicECS/SFML/Components/WritableContentComponent.hpp"
#include "GraphicECS/SFML/Resources/GraphicsFontResource.hpp"
#include "GraphicECS/SFML/Resources/GraphicsTextureResource.hpp"
#include "GraphicECS/SFML/Resources/MusicResource.hpp"
#include "GraphicECS/SFML/Resources/RenderWindowResource.hpp"
#include "GraphicECS/SFML/Resources/SoundResource.hpp"
#include "GraphicECS/SFML/Systems/AnimationSystem.hpp"
#include "GraphicECS/SFML/Systems/DrawComponents.hpp"
#include "GraphicECS/SFML/Systems/InputManagement.hpp"
#include "GraphicECS/SFML/Systems/MusicManagement.hpp"
#include "GraphicECS/SFML/Systems/ParallaxSystem.hpp"
#include "GraphicECS/SFML/Systems/RemoveChatSystem.hpp"
#include "GraphicECS/SFML/Systems/SfObjectFollowEntitySystem.hpp"
#include "GraphicECS/SFML/Systems/SoundManagement.hpp"
#include "GraphicECS/SFML/Systems/UpdateParallaxSystem.hpp"
#include "Transisthor/TransisthorECSLogic/Both/Components/Networkable.hpp"
#include "Transisthor/TransisthorECSLogic/Client/Components/NetworkServer.hpp"
#include "Transisthor/TransisthorECSLogic/Client/Systems/SendNewlyCreatedToServer.hpp"
#include "Transisthor/TransisthorECSLogic/Client/Systems/SendToServer.hpp"
#include "UserConnection.hpp"
#include "R-TypeLogic/EntityManipulation/ButtonManipulation/SharedResources/ButtonActionMap.hpp"
#include "R-TypeLogic/EntityManipulation/ButtonManipulation/SharedResources/GameStates.hpp"
#include "R-TypeLogic/EntityManipulation/ButtonManipulation/SharedResources/MenuStates.hpp"
#include "R-TypeLogic/EntityManipulation/CreateEntitiesFunctions/CreateButton.hpp"
#include "R-TypeLogic/EntityManipulation/CreateEntitiesFunctions/CreateChatMessage.hpp"
#include "R-TypeLogic/EntityManipulation/CreateEntitiesFunctions/CreateEnemy.hpp"
#include "R-TypeLogic/EntityManipulation/CreateEntitiesFunctions/CreatePlayer.hpp"
#include "R-TypeLogic/EntityManipulation/CreateEntitiesFunctions/CreateWritable.hpp"
#include "R-TypeLogic/EntityManipulation/CreateEntitiesFunctions/CreateWritableButton.hpp"
#include "R-TypeLogic/Global/Components/AlliedProjectileComponent.hpp"
#include "R-TypeLogic/Global/Components/DamageComponent.hpp"
#include "R-TypeLogic/Global/Components/DamageRadiusComponent.hpp"
#include "R-TypeLogic/Global/Components/DisconnectableComponent.hpp"
#include "R-TypeLogic/Global/Components/EnemyComponent.hpp"
#include "R-TypeLogic/Global/Components/EnemyProjectileComponent.hpp"
#include "R-TypeLogic/Global/Components/LayerLvL.hpp"
#include "R-TypeLogic/Global/Components/ObstacleComponent.hpp"
#include "R-TypeLogic/Global/Components/PlayerComponent.hpp"
#include "R-TypeLogic/Global/Components/PositionComponent.hpp"
#include "R-TypeLogic/Global/Components/ProjectileComponent.hpp"
#include "R-TypeLogic/Global/SharedResources/GameClock.hpp"
#include "R-TypeLogic/Global/SharedResources/Random.hpp"
#include "R-TypeLogic/Global/Systems/DeathSystem.hpp"
#include "R-TypeLogic/Global/Systems/ElectricInvisibleEnemySystem.hpp"
#include "R-TypeLogic/Global/Systems/MovementSystem.hpp"
#include "R-TypeLogic/Global/Systems/NoAfkInMenuSystem.hpp"
#include "R-TypeLogic/Global/Systems/UpdateClockSystem.hpp"
#include "R-TypeLogic/Server/Systems/CollidableSystem.hpp"
#include "R-TypeLogic/Server/Systems/DeathLifeSystem.hpp"
#include "R-TypeLogic/Server/Systems/DecreaseLifeTimeSystem.hpp"
#include "R-TypeLogic/Server/Systems/DisconnectableSystem.hpp"
#include "R-TypeLogic/Server/Systems/EnemiesPatterns.hpp"
#include "R-TypeLogic/Server/Systems/EnemyShootSystem.hpp"
#include "R-TypeLogic/Server/Systems/LifeTimeDeathSystem.hpp"
#include "R-TypeLogic/Server/Systems/MobGenerationSystem.hpp"

using namespace error_lib;
using namespace communicator_lib;
using namespace client_data;
using namespace ecs;
using namespace graphicECS::SFML::Systems;
using namespace graphicECS::SFML::Components;
using namespace graphicECS::SFML::Resources;

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

void ClientRoom::_startConnexionProtocol(void)
{
    void *networkData = std::malloc(sizeof(char) * 10);

    if (networkData == nullptr)
        throw MallocError("Malloc failed.");
    std::memcpy(networkData, _pseudo.c_str(), sizeof(char) * 5);
    std::memcpy((void *)((char *)networkData + sizeof(char) * 5), _password.c_str(), sizeof(char) * 5);
    _communicatorInstance.get()->startReceiverListening();
    _communicatorInstance.get()->sendDataToAClient(_serverEndpoint, networkData, sizeof(char) * 10, 14);
    std::free(networkData);
}
void ClientRoom::_protocol12Answer(CommunicatorMessage connexionResponse)
{
    _worldInstance.get()->addEntity().addComponent<NetworkServer>(connexionResponse.message.clientInfo.getId());
    auto &clock = _worldInstance.get()->getResource<GameClock>();
    auto guard = std::lock_guard(clock);
    clock.resetClock();
    clock.resetClock();
}

void ClientRoom::_holdAChatRequest(CommunicatorMessage chatRequest)
{
    std::vector<std::string> chatInformation = _communicatorInstance->utilitaryReceiveChatMessage(chatRequest);
    std::vector<std::shared_ptr<ecs::Entity>> joined = _worldInstance->joinEntities<ChatMessage>();

    auto moveChatPos = [](std::shared_ptr<ecs::Entity> entityPtr) {
        auto &pos = entityPtr->getComponent<Position>();
        auto &text = entityPtr->getComponent<GraphicsTextComponent>();

        pos.y -= 50;
        text.text.setPosition(text.text.getPosition().x, text.text.getPosition().y - 50);
    };

    std::for_each(joined.begin(), joined.end(), moveChatPos);
    createNewChatMessage(
        *(_worldInstance.get()), 1470, 840, 310, 45, 5.0, chatInformation.at(0), chatInformation.at(1));

    std::cerr << "Receiving a new chat from " << chatInformation.at(0) << " : " << chatInformation.at(1) << std::endl;
}

void ClientRoom::_protocol15Answer(CommunicatorMessage connectionResponse)
{
    unsigned short roomNumber = 0;
    std::size_t offset = sizeof(unsigned short);
    sf::Vector2u windowSize = _worldInstance->getResource<RenderWindowResource>().window.getSize();

    std::memcpy(&roomNumber, connectionResponse.message.data, sizeof(unsigned short));
    std::size_t id = createNewWritable(*(_worldInstance.get()), windowSize.x - 300, 100, 200, 50, MenuStates::LOBBY);
    createNewWritableButton(*(_worldInstance.get()), windowSize.x - 300, 200, 200, 50,
        std::function<void(World &, Entity &, std::string &)>(createARoom), MenuStates::LOBBY, id);
    for (int i = 0; i < roomNumber; i++) {
        unsigned short roomId = 0;
        unsigned short nameSize = 0;
        std::memcpy(&roomId, (void *)((char *)connectionResponse.message.data + offset), sizeof(unsigned short));
        offset += sizeof(unsigned short);
        std::memcpy(&nameSize, (void *)((char *)connectionResponse.message.data + offset), sizeof(unsigned short));
        offset += sizeof(unsigned short);
        char *tempRoomName = (char *)connectionResponse.message.data + offset;
        std::string roomName(nameSize, '\0');
        for (int j = 0; j < nameSize; j++)
            roomName[j] = tempRoomName[j];
        offset += sizeof(char) * nameSize;
        createNewButton(*(_worldInstance.get()), windowSize.x / 2 - 100, i * 60, 200, 50,
            ButtonActionMap::ROOM_CONNECTION, LayerLvL::BUTTON, MenuStates::LOBBY, std::to_string(i) + roomName);
    }
}

void ClientRoom::_signalSoloCallbackHandler(int signum)
{
    (void)signum;
    std::cerr << "Room ask to be closed." << std::endl;
    _state = ClientState::ENDED;
}

void ClientRoom::_initSoloData(void)
{
    createNewPlayer(*_worldInstance.get(), 20, 500, 0, 0, 1, 102, 102, 100, 10, 4, true, 1, _pseudo);
}

void ClientRoom::_startSoloLoop()
{
    std::signal(SIGINT, signalCallbackHandler);
    _initSoloData();
    _state = ClientState::MAIN_MENU;
    _updateEcsData(true);
    while (_state != ClientState::ENDED && _state != ClientState::UNDEFINED) {
        if (_worldInstance->containsResource<MenuStates>()
            && _worldInstance->getResource<MenuStates>().currentState == MenuStates::LOBBY) {
            _worldInstance->getResource<MenuStates>().currentState = MenuStates::IN_GAME;
            _state = ClientState::IN_GAME;
            _updateEcsData(true);
        }
        _worldInstance.get()->runSystems();
    }
}

int ClientRoom::_choosePlayerInfosForServer()
{
    UserConnection connection;
    std::string pseudo;
    std::string password;

    try {
        connection.userConnection();
    } catch (error_lib::RTypeError &e) {
        std::cerr << e.what() << std::endl;
        return (84);
    }
    pseudo = connection.getPseudo();
    password = connection.getPassword();
    connection.~UserConnection();
    startLobbyLoop(pseudo, password, false);
    return 0;
}

void ClientRoom::_getClientPseudoAndPassword()
{
    std::string pseudo;

    std::cerr << "Welcome to the R-Type game !" << std::endl;
    std::cerr << "You are in Solo mode ! Please enter your Pseudo" << std::endl;
    std::cerr << "Please refer your pseudonyme (5 characters): ";
    std::cin >> pseudo;
    if (pseudo.size() != 5) {
        std::cerr << "Nop ! Please enter a 5 characters pseudonyme.";
        _state = ClientState::ENDED;
        return;
    }
    _pseudo = pseudo;
}

int ClientRoom::startGame()
{
    std::cerr << "If you want to play in Solo Mode, please refer S. Otherwise if you want to play in multiplayer use M "
                 "and be sure that a server is running : ";
    char choosedMode = '\0';

    std::cin >> choosedMode;
    if (choosedMode == 'S') {
        _getClientPseudoAndPassword();
        _startSoloLoop();
    } else if (choosedMode == 'M') {
        if (_choosePlayerInfosForServer() == 84)
            return 84;
    } else {
        std::cerr << "Not a valid option ;)" << std::endl;
        _state = ClientState::ENDED;
    }
    return 0;
}

void ClientRoom::_connectToARoom()
{
    void *networkData = std::malloc(sizeof(char) * 5);

    if (networkData == nullptr)
        throw MallocError("Malloc failed.");
    std::memcpy(networkData, _pseudo.c_str(), sizeof(char) * 5);
    _communicatorInstance.get()->sendDataToAClient(_serverEndpoint, networkData, sizeof(char) * 5, 10);
    std::free(networkData);
}

void ClientRoom::_disconectionProcess()
{
    _communicatorInstance.get()->sendDataToAClient(_serverEndpoint, nullptr, 0, 13);
}

void ClientRoom::_holdADisconnectionRequest() { _state = ClientState::ENDED; }

void ClientRoom::_updateEcsResources(bool isSolo)
{
    if (!_worldInstance->containsResource<RandomDevice>())
        _worldInstance->addResource<RandomDevice>();
    if (!_worldInstance->containsResource<GameClock>())
        _worldInstance->addResource<GameClock>();
    if (!_worldInstance->containsResource<RenderWindowResource>())
        _worldInstance->addResource<RenderWindowResource>();
    if (!_worldInstance->containsResource<GraphicsFontResource>())
        _worldInstance->addResource<GraphicsFontResource>(FONT_PATH);
    if (!_worldInstance->containsResource<MenuStates>())
        _worldInstance->addResource<MenuStates>(MenuStates::MAIN_MENU);
    if (!_worldInstance->containsResource<MusicResource>())
        _worldInstance->addResource<MusicResource>();
    if (!_worldInstance->containsResource<SoundResource>())
        _worldInstance->addResource<SoundResource>();
    if (!_worldInstance->containsResource<GameStates>())
        _worldInstance->addResource<GameStates>(GameStates::IN_PAUSED);
    if (!_worldInstance->containsResource<GraphicsTextureResource>())
        _worldInstance->addResource<GraphicsTextureResource>();
    if (!_worldInstance->containsResource<ButtonActionMap>())
        _worldInstance->addResource<ButtonActionMap>();
    if (!_worldInstance->containsResource<GameLevel>())
        _worldInstance->addResource<GameLevel>();
    if (_worldInstance->containsResource<GraphicsTextureResource>())
        _loadTextures();
    if (_worldInstance->containsResource<ButtonActionMap>())
        _loadButtonActionMap(isSolo);
}

void ClientRoom::_loadTextures()
{
    GraphicsTextureResource &textureResource = _worldInstance->getResource<GraphicsTextureResource>();
    auto guard = std::lock_guard(textureResource);

    textureResource.addTexture(
        GraphicsTextureResource::BUTTON, BUTTON_TEXTURE_PATH, sf::Vector2f(34, 0), sf::Vector2f(34, 34));
    textureResource.addTexture(
        GraphicsTextureResource::BASIC_ENEMY, BASIC_ENEMY_TEXTURE_PATH, sf::Vector2f(0, 0), sf::Vector2f(34, 34));
    textureResource.addTexture(
        GraphicsTextureResource::ELECTRIC_ENEMY, ELECTRIC_ENEMY_TEXTURE_PATH, sf::Vector2f(0, 0), sf::Vector2f(34, 34));
    textureResource.addTexture(
        GraphicsTextureResource::FIRE_ENEMY, FIRE_ENEMY_TEXTURE_PATH, sf::Vector2f(0, 0), sf::Vector2f(34, 34));
    textureResource.addTexture(
        GraphicsTextureResource::ICE_ENEMY, ICE_ENEMY_TEXTURE_PATH, sf::Vector2f(0, 0), sf::Vector2f(34, 34));
    _initWritableTextures(textureResource);
    _initPlayerTextures(textureResource);
    _initProjectilesTextures(textureResource);
    _initBackgroundsTextures(textureResource);
}

void ClientRoom::_initProjectilesTextures(GraphicsTextureResource &textureResource)
{
    textureResource.addTexture(GraphicsTextureResource::PROJECTILE_ENEMY_BASIC, BASIC_ENEMY_PROJECTILE_TEXTURE_PATH,
        sf::Vector2f(0, 0), sf::Vector2f(34, 34));
    textureResource.addTexture(GraphicsTextureResource::PROJECTILE_ENEMY_FIRE, FIRE_ENEMY_PROJECTILE_TEXTURE_PATH,
        sf::Vector2f(0, 0), sf::Vector2f(34, 34));
    textureResource.addTexture(GraphicsTextureResource::PROJECTILE_ENEMY_ELECTRIC,
        ELECTRIC_ENEMY_PROJECTILE_TEXTURE_PATH, sf::Vector2f(0, 0), sf::Vector2f(34, 34));
    textureResource.addTexture(GraphicsTextureResource::PROJECTILE_ENEMY_ICE, ICE_ENEMY_PROJECTILE_TEXTURE_PATH,
        sf::Vector2f(0, 0), sf::Vector2f(34, 34));
    textureResource.addTexture(GraphicsTextureResource::PROJECTILE_ALLY, BASIC_ALLIED_PROJECTILE_TEXTURE_PATH,
        sf::Vector2f(0, 0), sf::Vector2f(20, 20));
    textureResource.addTexture(
        GraphicsTextureResource::BOSS, BOSS_TEXTURE_PATH, sf::Vector2f(0, 0), sf::Vector2f(50, 57));
}

void ClientRoom::_initBackgroundsTextures(GraphicsTextureResource &textureResource)
{
    textureResource.addTexture(GraphicsTextureResource::BACKGROUND_LAYER_3, BACK_BACKGROUND_TEXTURE_PATH,
        sf::Vector2f(0, 0), sf::Vector2f(1920, 1080));
    textureResource.addTexture(GraphicsTextureResource::BACKGROUND_LAYER_2, FAR_BACKGROUND_TEXTURE_PATH,
        sf::Vector2f(0, 0), sf::Vector2f(1920, 1080));
    textureResource.addTexture(GraphicsTextureResource::BACKGROUND_LAYER_1, MIDDLE_BACKGROUND_TEXTURE_PATH,
        sf::Vector2f(0, 0), sf::Vector2f(1920, 1080));
}

void ClientRoom::_initWritableTextures(GraphicsTextureResource &textureResource)
{
    textureResource.addTexture(
        GraphicsTextureResource::WRITABLE, WRITABLE_TEXTURE_PATH, sf::Vector2f(34, 0), sf::Vector2f(34, 34));
    textureResource.addTexture(GraphicsTextureResource::WRITABLE_SELECTED, WRITABLE_SELECTED_TEXTURE_PATH,
        sf::Vector2f(534 / 16 * 8, 0), sf::Vector2f(534 / 16, 34));
    textureResource.addTexture(GraphicsTextureResource::WRITABLE_BUTTON, WRITABLE_BUTTON_TEXTURE_PATH,
        sf::Vector2f(34, 0), sf::Vector2f(34, 34));
}

void ClientRoom::_initPlayerTextures(GraphicsTextureResource &textureResource)
{
    textureResource.addTexture(GraphicsTextureResource::PLAYER_STATIC_1, PLAYER_TEXTURE_PATH,
        sf::Vector2f(534 / 16 * 8, 0), sf::Vector2f(534 / 16, 34));
    textureResource.addTexture(GraphicsTextureResource::PLAYER_STATIC_2, PLAYER_TEXTURE_PATH,
        sf::Vector2f(534 / 16 * 9, 0), sf::Vector2f(534 / 16, 34));
    textureResource.addTexture(GraphicsTextureResource::PLAYER_STATIC_3, PLAYER_TEXTURE_PATH,
        sf::Vector2f(534 / 16 * 10, 0), sf::Vector2f(534 / 16, 34));
    textureResource.addTexture(GraphicsTextureResource::PLAYER_STATIC_4, PLAYER_TEXTURE_PATH,
        sf::Vector2f(534 / 16 * 11, 0), sf::Vector2f(534 / 16, 34));
    textureResource.addTexture(GraphicsTextureResource::PLAYER_STATIC_5, PLAYER_TEXTURE_PATH,
        sf::Vector2f(534 / 16 * 12, 0), sf::Vector2f(534 / 16, 34));
    textureResource.addTexture(GraphicsTextureResource::PLAYER_STATIC_6, PLAYER_TEXTURE_PATH,
        sf::Vector2f(534 / 16 * 13, 0), sf::Vector2f(534 / 16, 34));
    textureResource.addTexture(GraphicsTextureResource::PLAYER_STATIC_7, PLAYER_TEXTURE_PATH,
        sf::Vector2f(534 / 16 * 14, 0), sf::Vector2f(534 / 16, 34));
    textureResource.addTexture(GraphicsTextureResource::PLAYER_STATIC_8, PLAYER_TEXTURE_PATH,
        sf::Vector2f(534 / 16 * 15, 0), sf::Vector2f(534 / 16, 34));
}

void ClientRoom::_loadButtonActionMap(bool isSolo)
{
    ButtonActionMap &actionsList = _worldInstance->getResource<ButtonActionMap>();

    actionsList.addAction(ButtonActionMap::PAUSE, std::function<void(World &, Entity &)>(pauseGame));
    actionsList.addAction(ButtonActionMap::RESUME, std::function<void(World &, Entity &)>(resumeGame));
    actionsList.addAction(ButtonActionMap::EXIT, std::function<void(World &, Entity &)>(exitWindow));
    actionsList.addAction(ButtonActionMap::WRITABLE, std::function<void(World &, Entity &)>(selectAWritable));
    actionsList.addAction(
        ButtonActionMap::WRITABLE_BUTTON, std::function<void(World &, Entity &)>(writableButtonAction));
    if (isSolo) {
        actionsList.addAction(ButtonActionMap::LOBBY, std::function<void(World &, Entity &)>(launchSoloGame));
    } else {
        actionsList.addAction(ButtonActionMap::LOBBY, std::function<void(World &, Entity &)>(goToLobby));
        actionsList.addAction(ButtonActionMap::ROOM_CONNECTION, std::function<void(World &, Entity &)>(connectToARoom));
    }
}

void ClientRoom::_updateEcsEntities()
{
    if (_worldInstance
            ->joinEntities<MouseInputComponent, KeyboardInputComponent, ControllerButtonInputComponent,
                ControllerJoystickInputComponent, ActionQueueComponent, AllowMouseAndKeyboardComponent,
                AllowControllerComponent>()
            .empty())
        _initInputsEntity();
    if (_state == ClientState::MAIN_MENU) {
        _initMainMenuButtons();
    }
    if (_state == ClientState::LOBBY) {}
    if (_state == ClientState::IN_GAME) {
        _initInGameButtons();
        _initInGameWritables();
        _initInGameBackgrounds();
    }
}

void ClientRoom::_initInputsEntity()
{
    ecs::Entity &entity = _worldInstance->addEntity()
                              .addComponent<MouseInputComponent>()
                              .addComponent<KeyboardInputComponent>()
                              .addComponent<ControllerButtonInputComponent>()
                              .addComponent<ControllerJoystickInputComponent>()
                              .addComponent<ActionQueueComponent>()
                              .addComponent<AllowMouseAndKeyboardComponent>()
                              .addComponent<AllowControllerComponent>();

    entity.getComponent<KeyboardInputComponent>().keyboardMapActions.emplace(
        std::make_pair<sf::Keyboard::Key, std::pair<ActionQueueComponent::inputAction_e, float>>(sf::Keyboard::Z,
            std::make_pair<ActionQueueComponent::inputAction_e, float>(ActionQueueComponent::MOVEY, -200)));
    entity.getComponent<KeyboardInputComponent>().keyboardMapActions.emplace(
        std::make_pair<sf::Keyboard::Key, std::pair<ActionQueueComponent::inputAction_e, float>>(sf::Keyboard::S,
            std::make_pair<ActionQueueComponent::inputAction_e, float>(ActionQueueComponent::MOVEY, 200)));
    entity.getComponent<KeyboardInputComponent>().keyboardMapActions.emplace(
        std::make_pair<sf::Keyboard::Key, std::pair<ActionQueueComponent::inputAction_e, float>>(sf::Keyboard::Q,
            std::make_pair<ActionQueueComponent::inputAction_e, float>(ActionQueueComponent::MOVEX, -200)));
    entity.getComponent<KeyboardInputComponent>().keyboardMapActions.emplace(
        std::make_pair<sf::Keyboard::Key, std::pair<ActionQueueComponent::inputAction_e, float>>(sf::Keyboard::D,
            std::make_pair<ActionQueueComponent::inputAction_e, float>(ActionQueueComponent::MOVEX, 200)));
    entity.getComponent<KeyboardInputComponent>().keyboardMapActions.emplace(
        std::make_pair<sf::Keyboard::Key, std::pair<ActionQueueComponent::inputAction_e, float>>(sf::Keyboard::Enter,
            std::make_pair<ActionQueueComponent::inputAction_e, float>(ActionQueueComponent::SHOOT, 10)));
    entity.getComponent<ControllerJoystickInputComponent>().controllerJoystickMapActions.emplace(
        std::make_pair<unsigned int, std::pair<ActionQueueComponent::inputAction_e, float>>(
            1, std::make_pair<ActionQueueComponent::inputAction_e, float>(ActionQueueComponent::MOVEY, 0)));
    entity.getComponent<MouseInputComponent>().MouseMapActions.emplace(
        std::make_pair<sf::Mouse::Button, std::pair<ActionQueueComponent::inputAction_e, float>>(
            sf::Mouse::Button::Left,
            std::make_pair<ActionQueueComponent::inputAction_e, float>(ActionQueueComponent::BUTTON_CLICK, 0)));
}

void ClientRoom::_initInGameButtons()
{
    createNewButton(
        *(_worldInstance.get()), 0, 0, 68, 68, ButtonActionMap::PAUSE, LayerLvL::BUTTON, MenuStates::IN_GAME, "Pause");
    createNewButton(*(_worldInstance.get()), 909, 200, 102, 102, ButtonActionMap::RESUME, LayerLvL::BUTTON,
        MenuStates::GAME_PAUSED, "Resume");
    createNewButton(*(_worldInstance.get()), 909, 500, 102, 102, ButtonActionMap::EXIT, LayerLvL::BUTTON,
        MenuStates::GAME_PAUSED, "Exit");
}

void ClientRoom::_initMainMenuButtons()
{
    sf::Vector2u windowSize(0, 0);

    if (_worldInstance->containsResource<RenderWindowResource>())
        windowSize = _worldInstance->getResource<RenderWindowResource>().window.getSize();
    createNewButton(*(_worldInstance.get()), windowSize.x / 2 - 100, windowSize.y / 3 - 25, 200, 50,
        ButtonActionMap::LOBBY, LayerLvL::BUTTON, MenuStates::MAIN_MENU, "Lobby");
    createNewButton(*(_worldInstance.get()), windowSize.x / 2 - 100, windowSize.y / 3 * 2 - 25, 200, 50,
        ButtonActionMap::EXIT, LayerLvL::BUTTON, MenuStates::MAIN_MENU, "Quit");
}

void ClientRoom::_initInGameWritables()
{
    std::size_t writableId = createNewWritable(*(_worldInstance.get()), 1450, 900, 350, 50, MenuStates::IN_GAME);

    createNewWritableButton(*(_worldInstance.get()), 1820, 900, 80, 50,
        std::function<void(World &, Entity &, std::string &)>(publishNewChatMessage), MenuStates::IN_GAME, writableId);
}

void ClientRoom::_updateEcsSystems(bool isSolo)
{
    if (!_worldInstance->containsSystem<UpdateClock>())
        _worldInstance->addSystem<UpdateClock>();
    if (!_worldInstance->containsSystem<DrawComponents>())
        _worldInstance->addSystem<DrawComponents>();
    if (!_worldInstance->containsSystem<InputManagement>())
        _worldInstance->addSystem<InputManagement>();
    if (!_worldInstance->containsSystem<Parallax>())
        _worldInstance->addSystem<Parallax>();
    if (!_worldInstance->containsSystem<MusicManagement>())
        _worldInstance->addSystem<MusicManagement>();
    if (!_worldInstance->containsSystem<SoundManagement>())
        _worldInstance->addSystem<SoundManagement>();
    if (!_worldInstance->containsSystem<DeathSystem>())
        _worldInstance->addSystem<DeathSystem>();
    if (!_worldInstance->containsSystem<SfObjectFollowEntitySystem>())
        _worldInstance->addSystem<SfObjectFollowEntitySystem>();
    if (!_worldInstance->containsSystem<Movement>())
        _worldInstance->addSystem<Movement>();
    if (!_worldInstance->containsSystem<AnimationSystem>())
        _worldInstance->addSystem<AnimationSystem>();
    if (!_worldInstance->containsSystem<NoAfkInMenu>())
        _worldInstance->addSystem<NoAfkInMenu>();
    if (!_worldInstance->containsSystem<RemoveChatSystem>())
        _worldInstance->addSystem<RemoveChatSystem>();
    if (!_worldInstance->containsSystem<ElectricInvisibleEnemy>())
        _worldInstance->addSystem<ElectricInvisibleEnemy>();
    if (!_worldInstance->containsSystem<UpdateParallax>())
        _worldInstance->addSystem<UpdateParallax>();
    if (isSolo) {
        if (!_worldInstance->containsSystem<MobGeneration>() && _state == ClientState::IN_GAME)
            _worldInstance->addSystem<MobGeneration>();
        if (!_worldInstance->containsSystem<EnemiesPatterns>())
            _worldInstance->addSystem<EnemiesPatterns>();
        if (!_worldInstance->containsSystem<EnemyShootSystem>())
            _worldInstance->addSystem<EnemyShootSystem>();
        if (!_worldInstance->containsSystem<Collide>())
            _worldInstance->addSystem<Collide>();
        if (!_worldInstance->containsSystem<DeathLife>())
            _worldInstance->addSystem<DeathLife>();
        if (!_worldInstance->containsSystem<LifeTimeDeath>())
            _worldInstance->addSystem<LifeTimeDeath>();
        if (!_worldInstance->containsSystem<DecreaseLifeTime>())
            _worldInstance->addSystem<DecreaseLifeTime>();
    } else {
        if (!_worldInstance->containsSystem<SendToServer>())
            _worldInstance->addSystem<SendToServer>();
        if (!_worldInstance->containsSystem<SendNewlyCreatedToServer>())
            _worldInstance->addSystem<SendNewlyCreatedToServer>();
    }
}

void ClientRoom::_updateEcsData(bool isSolo)
{
    _updateEcsResources(isSolo);
    _updateEcsEntities();
    _updateEcsSystems(isSolo);
}

bool ClientRoom::_answerProtocols(bool isSolo)
{
    CommunicatorMessage connectionOperation;

    try {
        connectionOperation = _communicatorInstance.get()->getLastMessage();
        if (connectionOperation.message.type == 11) {
            std::cerr << "No places left inside the hub. Please retry later" << std::endl;
            return false;
        }
        if (connectionOperation.message.type == 13) {
            _holdADisconnectionRequest();
        }
        if (connectionOperation.message.type == 20) {
            _serverEndpoint = _communicatorInstance->getClientByHisId(_communicatorInstance->getServerEndpointId());
            _connectToARoom();
        }
        if (connectionOperation.message.type == 15) {
            _protocol15Answer(connectionOperation);
        }
        if (connectionOperation.message.type == 12) {
            _protocol12Answer(connectionOperation);
            _updateEcsData(isSolo);
        }
        if (connectionOperation.message.type == 50) {
            if (_state == ClientState::IN_GAME)
                _holdAChatRequest(connectionOperation);
        }
    } catch (NetworkError &error) {
    }
    return true;
}

void ClientRoom::startLobbyLoop(const std::string &pseudo, const std::string &password, bool isSolo)
{
    _pseudo = pseudo;
    _password = password;
    std::signal(SIGINT, signalCallbackHandler);
    if (_state != ClientState::ENDED)
        _startConnexionProtocol();
    _state = ClientState::MAIN_MENU;
    _updateEcsData(isSolo);
    while (_state != ClientState::ENDED) {
        if (!_answerProtocols(isSolo))
            return;
        if (_worldInstance->containsResource<MenuStates>()) {
            if (_worldInstance->getResource<MenuStates>().currentState == MenuStates::LOBBY
                && _state != ClientRoom::LOBBY) {
                _state = ClientState::LOBBY;
                _updateEcsData(false);
            }
            if (_worldInstance->getResource<MenuStates>().currentState == MenuStates::IN_GAME
                && _state != ClientRoom::IN_GAME) {
                _state = ClientState::IN_GAME;
                _updateEcsData(false);
            }
        }
        _worldInstance.get()->runSystems(); /// WILL BE IMPROVED IN PART TWO (THREAD + CLOCK)
    }
    _disconectionProcess();
}

void ClientRoom::_initInGameBackgrounds()
{
    size_t firstID =
        _worldInstance->addEntity()
            .addComponent<ParallaxBackground>()
            .addComponent<GraphicsRectangleComponent>(-1920, 0, 1920, 1080)
            .addComponent<Position>(1920, 0)
            .addComponent<Velocity>(-300, 0)
            .addComponent<LayerLvL>(LayerLvL::layer_e::DECORATION)
            .addComponent<TextureName>(GraphicsTextureResource::BACKGROUND_LAYER_1)
            .addComponent<MusicComponent>(MusicResource::music_e::BACKGROUNDTHEME, sf::SoundSource::Status::Playing)
            .addComponent<SoundComponent>(SoundResource::sound_e::SHOOT, sf::SoundSource::Status::Playing)
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
