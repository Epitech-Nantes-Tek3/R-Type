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
#include "Transisthor/TransisthorECSLogic/Both/Components/Networkable.hpp"
#include "Transisthor/TransisthorECSLogic/Client/Components/NetworkServer.hpp"
#include "Transisthor/TransisthorECSLogic/Client/Systems/SendNewlyCreatedToServer.hpp"
#include "Transisthor/TransisthorECSLogic/Client/Systems/SendToServer.hpp"
#include "R-TypeLogic/EntityManipulation/ButtonManipulation/SharedResources/ButtonActionMap.hpp"
#include "R-TypeLogic/EntityManipulation/ButtonManipulation/SharedResources/GameStates.hpp"
#include "R-TypeLogic/EntityManipulation/ButtonManipulation/SharedResources/MenuStates.hpp"
#include "R-TypeLogic/EntityManipulation/CreateEntitiesFunctions/CreateButton.hpp"
#include "R-TypeLogic/EntityManipulation/CreateEntitiesFunctions/CreateChatMessage.hpp"
#include "R-TypeLogic/EntityManipulation/CreateEntitiesFunctions/CreateWritable.hpp"
#include "R-TypeLogic/EntityManipulation/CreateEntitiesFunctions/CreateWritableButton.hpp"
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

void ClientRoom::_initEcsGameData(void)
{
    _initSharedResources();
    _initSystems();
    _initEntities();
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

void ClientRoom::protocol12Answer(CommunicatorMessage connexionResponse)
{
    _state = ClientState::IN_GAME;
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
        short configs[6] = {120, 121, 122, 123, 124, 125};
        _communicatorInstance.get()->utilitarySendRoomConfiguration(roomName, configs, _serverEndpoint);
    } else {
        std::cerr << "Not a valid option ;)" << std::endl;
        _state = ClientState::ENDED;
    }
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

bool ClientRoom::_answerProtocols()
{
    CommunicatorMessage connectionOperation;

    try {
        connectionOperation = _communicatorInstance.get()->getLastMessage();
        switch (connectionOperation.message.type) {
            case 11: std::cerr << "No places left inside the hub. Please retry later" << std::endl; return false;
            case 13: _holdADisconnectionRequest(); break;
            case 20:
                _serverEndpoint = _communicatorInstance->getClientByHisId(_communicatorInstance->getServerEndpointId());
                _initEcsGameData();
                _connectToARoom();
                break;
            case 15:
                if (_state == ClientState::MAIN_MENU)
                    _protocol15Answer(connectionOperation);
                break;
            case 12:
                if (_state == ClientState::MAIN_MENU)
                    protocol12Answer(connectionOperation);
                break;
            case 50:
                if (_state == ClientState::IN_GAME)
                    _holdAChatRequest(connectionOperation);
                break;
        }
    } catch (NetworkError &error) {
    }
    return true;
}

void ClientRoom::_loadTextures()
{
    GraphicsTextureResource &textureResource = _worldInstance->getResource<GraphicsTextureResource>();
    auto guard = std::lock_guard(textureResource);

    textureResource.addTexture(GraphicsTextureResource::BUTTON, "assets/EpiSprite/r-typesheet11.gif",
        sf::Vector2f(34, 0), sf::Vector2f(34, 34));
    textureResource.addTexture(GraphicsTextureResource::ENEMY_STATIC, "assets/EpiSprite/BasicEnemySpriteSheet.gif",
        sf::Vector2f(0, 0), sf::Vector2f(34, 34));
    _initWritableTextures(textureResource);
    _initPlayerTextures(textureResource);
    _initProjectilesTextures(textureResource);
    _initBackgroundsTextures(textureResource);
}

void ClientRoom::_loadButtonActionMap()
{
    ButtonActionMap &actionsList = _worldInstance->getResource<ButtonActionMap>();

    actionsList.addAction(ButtonActionMap::PAUSE, std::function<void(World &, Entity &)>(pauseGame));
    actionsList.addAction(ButtonActionMap::RESUME, std::function<void(World &, Entity &)>(resumeGame));
    actionsList.addAction(ButtonActionMap::EXIT, std::function<void(World &, Entity &)>(exitWindow));
    actionsList.addAction(ButtonActionMap::WRITABLE, std::function<void(World &, Entity &)>(selectAWritable));
    actionsList.addAction(
        ButtonActionMap::WRITABLE_BUTTON, std::function<void(World &, Entity &)>(writableButtonAction));
}

void ClientRoom::_updateEcsResources()
{
    // MusicResource::music_e::BACKGROUNDTHEME, "assets/Musics/music_background.wav"
    // SoundResource::sound_e::SHOOT, "assets/Sounds/sound.wav"

    if (!_worldInstance->containsResource<RandomDevice>())
        _worldInstance->addResource<RandomDevice>();
    if (!_worldInstance->containsResource<GameClock>())
        _worldInstance->addResource<GameClock>();
    if (!_worldInstance->containsResource<RenderWindowResource>())
        _worldInstance->addResource<RenderWindowResource>();
    if (!_worldInstance->containsResource<GraphicsFontResource>())
        _worldInstance->addResource<GraphicsFontResource>("assets/fonts/arial.ttf");
    if (!_worldInstance->containsResource<MenuStates>())
        _worldInstance->addResource<MenuStates>(MenuStates::IN_GAME);
    if (!_worldInstance->containsResource<MusicResource>())
        _worldInstance->addResource<MusicResource>();
    if (!_worldInstance->containsResource<SoundResource>())
        _worldInstance->addResource<SoundResource>();
    if (!_worldInstance->containsResource<GameStates>())
        _worldInstance->addResource<GameStates>(GameStates::IN_GAME);
    if (!_worldInstance->containsResource<GraphicsTextureResource>())
        _worldInstance->addResource<GraphicsTextureResource>();
    if (!_worldInstance->containsResource<ButtonActionMap>())
        _worldInstance->addResource<ButtonActionMap>();
    if (_worldInstance->containsResource<GraphicsTextureResource>())
        _loadTextures();
    if (_worldInstance->containsResource<ButtonActionMap>())
        _loadButtonActionMap();
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

void ClientRoom::_initInGameBackgrounds()
{

}

void ClientRoom::_updateEcsEntities()
{
    _initInputsEntity();
    if (_state == ClientState::MAIN_MENU) {}
    if (_state == ClientState::LOBBY) {}
    if (_state == ClientState::IN_GAME) {
        _initInGameButtons();
        _initInGameWritables();
        _initInGameBackgrounds();
    }
}

void ClientRoom::_updateEcsSystems()
{
    if (!_worldInstance->containsSystem<UpdateClock>())
        _worldInstance->addSystem<UpdateClock>();
    if (!_worldInstance->containsSystem<DrawComponents>())
        _worldInstance->addSystem<DrawComponents>();
    if (!_worldInstance->containsSystem<InputManagement>())
        _worldInstance->addSystem<InputManagement>();
    if (!_worldInstance->containsSystem<SendToServer>())
        _worldInstance->addSystem<SendToServer>();
    if (!_worldInstance->containsSystem<SendNewlyCreatedToServer>())
        _worldInstance->addSystem<SendNewlyCreatedToServer>();
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
    if (!_worldInstance->containsSystem<AnimationSystem>())
        _worldInstance->addSystem<NoAfkInMenu>();
    if (!_worldInstance->containsSystem<RemoveChatSystem>())
        _worldInstance->addSystem<RemoveChatSystem>();
}

void ClientRoom::_updateEcsData()
{
    _updateEcsResources();
    _updateEcsEntities();
    _updateEcsSystems();
}

void ClientRoom::startLobbyLoop(const std::string &pseudo, const std::string &password)
{
    _pseudo = pseudo;
    _password = password;
    std::signal(SIGINT, signalCallbackHandler);
    if (_state != ClientState::ENDED)
        _startConnexionProtocol();
    _state = ClientState::MAIN_MENU;
    _updateEcsData();
    while (_state != ClientState::ENDED) {
        if (!_answerProtocols())
            return;
        _worldInstance.get()->runSystems(); /// WILL BE IMPROVED IN PART TWO (THREAD + CLOCK)
    }
    _disconectionProcess();
}

void ClientRoom::_disconectionProcess()
{
    _communicatorInstance.get()->sendDataToAClient(_serverEndpoint, nullptr, 0, 13);
}

void ClientRoom::_holdADisconnectionRequest() { _state = ClientState::ENDED; }

void ClientRoom::_initPlayerTextures(GraphicsTextureResource &textureResource)
{
    textureResource.addTexture(GraphicsTextureResource::PLAYER_STATIC_1, "assets/EpiSprite/BasicPlayerSpriteSheet.gif",
        sf::Vector2f(534 / 16 * 8, 0), sf::Vector2f(534 / 16, 34));
    textureResource.addTexture(GraphicsTextureResource::PLAYER_STATIC_2, "assets/EpiSprite/BasicPlayerSpriteSheet.gif",
        sf::Vector2f(534 / 16 * 9, 0), sf::Vector2f(534 / 16, 34));
    textureResource.addTexture(GraphicsTextureResource::PLAYER_STATIC_3, "assets/EpiSprite/BasicPlayerSpriteSheet.gif",
        sf::Vector2f(534 / 16 * 10, 0), sf::Vector2f(534 / 16, 34));
    textureResource.addTexture(GraphicsTextureResource::PLAYER_STATIC_4, "assets/EpiSprite/BasicPlayerSpriteSheet.gif",
        sf::Vector2f(534 / 16 * 11, 0), sf::Vector2f(534 / 16, 34));
    textureResource.addTexture(GraphicsTextureResource::PLAYER_STATIC_5, "assets/EpiSprite/BasicPlayerSpriteSheet.gif",
        sf::Vector2f(534 / 16 * 12, 0), sf::Vector2f(534 / 16, 34));
    textureResource.addTexture(GraphicsTextureResource::PLAYER_STATIC_6, "assets/EpiSprite/BasicPlayerSpriteSheet.gif",
        sf::Vector2f(534 / 16 * 13, 0), sf::Vector2f(534 / 16, 34));
    textureResource.addTexture(GraphicsTextureResource::PLAYER_STATIC_7, "assets/EpiSprite/BasicPlayerSpriteSheet.gif",
        sf::Vector2f(534 / 16 * 14, 0), sf::Vector2f(534 / 16, 34));
    textureResource.addTexture(GraphicsTextureResource::PLAYER_STATIC_8, "assets/EpiSprite/BasicPlayerSpriteSheet.gif",
        sf::Vector2f(534 / 16 * 15, 0), sf::Vector2f(534 / 16, 34));
}

void ClientRoom::_initProjectilesTextures(GraphicsTextureResource &textureResource)
{
    textureResource.addTexture(GraphicsTextureResource::PROJECTILE_ENEMY_BASIC,
        "assets/EpiSprite/BasicEnemyProjectileSpriteSheet.gif", sf::Vector2f(0, 0), sf::Vector2f(34, 34));
    textureResource.addTexture(GraphicsTextureResource::PROJECTILE_ENEMY_FIRE,
        "assets/EpiSprite/FireEnemyProjectileSpriteSheet.gif", sf::Vector2f(0, 0), sf::Vector2f(34, 34));
    textureResource.addTexture(GraphicsTextureResource::PROJECTILE_ENEMY_ELECTRIC,
        "assets/EpiSprite/ElectricEnemyProjectileSpriteSheet.gif", sf::Vector2f(0, 0), sf::Vector2f(34, 34));
    textureResource.addTexture(GraphicsTextureResource::PROJECTILE_ENEMY_ICE,
        "assets/EpiSprite/IceEnemyProjectileSpriteSheet.gif", sf::Vector2f(0, 0), sf::Vector2f(34, 34));
    textureResource.addTexture(GraphicsTextureResource::PROJECTILE_ALLY,
        "assets/EpiSprite/BasicAlliedProjectileSpriteSheet.gif", sf::Vector2f(0, 0), sf::Vector2f(20, 20));
}

void ClientRoom::_initBackgroundsTextures(GraphicsTextureResource &textureResource)
{
    textureResource.addTexture(GraphicsTextureResource::BACKGROUND_LAYER_3, "assets/Backgrounds/back.png",
        sf::Vector2f(0, 0), sf::Vector2f(1920, 1080));
    textureResource.addTexture(GraphicsTextureResource::BACKGROUND_LAYER_2, "assets/Backgrounds/far.png",
        sf::Vector2f(0, 0), sf::Vector2f(1920, 1080));
    textureResource.addTexture(GraphicsTextureResource::BACKGROUND_LAYER_1, "assets/Backgrounds/middle.png",
        sf::Vector2f(0, 0), sf::Vector2f(1920, 1080));
}

void ClientRoom::_initWritableTextures(GraphicsTextureResource &textureResource)
{
    textureResource.addTexture(GraphicsTextureResource::WRITABLE, "assets/EpiSprite/r-typesheet11.gif",
        sf::Vector2f(34, 0), sf::Vector2f(34, 34));
    textureResource.addTexture(GraphicsTextureResource::WRITABLE_SELECTED,
        "assets/EpiSprite/BasicPlayerSpriteSheet.gif", sf::Vector2f(534 / 16 * 8, 0), sf::Vector2f(534 / 16, 34));
    textureResource.addTexture(GraphicsTextureResource::WRITABLE_BUTTON, "assets/EpiSprite/r-typesheet11.gif",
        sf::Vector2f(34, 0), sf::Vector2f(34, 34));
}

void ClientRoom::_initBackgroundEntities()
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

void ClientRoom::_initEntities()
{
    _initBackgroundEntities();
}

void ClientRoom::_initInGameButtons()
{
    createNewButton(
        *(_worldInstance.get()), 0, 0, 68, 68, ButtonActionMap::PAUSE, LayerLvL::BUTTON, MenuStates::IN_GAME);
    createNewButton(*(_worldInstance.get()), 909, 200, 102, 102, ButtonActionMap::RESUME, LayerLvL::BUTTON,
        MenuStates::GAME_PAUSED);
    createNewButton(
        *(_worldInstance.get()), 909, 500, 102, 102, ButtonActionMap::EXIT, LayerLvL::BUTTON, MenuStates::GAME_PAUSED);
}

void ClientRoom::_initInGameWritables()
{
    std::size_t writableId = createNewWritable(*(_worldInstance.get()), 1450, 900, 350, 50, MenuStates::IN_GAME);

    createNewWritableButton(*(_worldInstance.get()), 1820, 900, 80, 50,
        std::function<void(World &, Entity &, std::string &)>(publishNewChatMessage), MenuStates::IN_GAME, writableId);
}
