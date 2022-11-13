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
#include "GraphicECS/SFML/Components/AssociatedIdComponent.hpp"
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
#include "GraphicECS/SFML/Systems/ApplyInputDelay.hpp"
#include "GraphicECS/SFML/Systems/DrawComponents.hpp"
#include "GraphicECS/SFML/Systems/InputManagement.hpp"
#include "GraphicECS/SFML/Systems/MusicManagement.hpp"
#include "GraphicECS/SFML/Systems/ParallaxSystem.hpp"
#include "GraphicECS/SFML/Systems/RemoveChatSystem.hpp"
#include "GraphicECS/SFML/Systems/SfObjectFollowEntitySystem.hpp"
#include "GraphicECS/SFML/Systems/SoundManagement.hpp"
#include "GraphicECS/SFML/Systems/UpdateLifeText.hpp"
#include "GraphicECS/SFML/Systems/UpdateParallaxSystem.hpp"
#include "Transisthor/TransisthorECSLogic/Both/Components/Networkable.hpp"
#include "Transisthor/TransisthorECSLogic/Client/Components/NetworkServer.hpp"
#include "Transisthor/TransisthorECSLogic/Client/Systems/SendNewlyCreatedToServer.hpp"
#include "Transisthor/TransisthorECSLogic/Client/Systems/SendToServer.hpp"
#include "UserConnection.hpp"
#include "R-TypeLogic/EntityManipulation/ButtonManipulation/SharedResources/ButtonActionMap.hpp"
#include "R-TypeLogic/EntityManipulation/ButtonManipulation/SharedResources/GameStates.hpp"
#include "R-TypeLogic/EntityManipulation/CreateEntitiesFunctions/CreateButton.hpp"
#include "R-TypeLogic/EntityManipulation/CreateEntitiesFunctions/CreateChatMessage.hpp"
#include "R-TypeLogic/EntityManipulation/CreateEntitiesFunctions/CreateEnemy.hpp"
#include "R-TypeLogic/EntityManipulation/CreateEntitiesFunctions/CreatePlayer.hpp"
#include "R-TypeLogic/EntityManipulation/CreateEntitiesFunctions/CreateText.hpp"
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
    _highInstanceEndpoint = Client();
    _highInstanceEndpoint.setId(0);
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
    _highInstanceEndpoint = Client(serverAddress, serverPort);
    _highInstanceEndpoint.setId(0);
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

void ClientRoom::_connectToARoom()
{
    unsigned short pseudoSize = _pseudo.size();
    void *networkData = std::malloc(sizeof(char) * pseudoSize + sizeof(unsigned short));
    unsigned short offset = 0;

    if (networkData == nullptr)
        throw MallocError("Malloc failed.");
    std::memcpy(networkData, &pseudoSize, sizeof(unsigned short));
    offset += sizeof(unsigned short);
    std::memcpy((void *)((char *)networkData + offset), _pseudo.c_str(), sizeof(char) * pseudoSize);
    offset += sizeof(char) * pseudoSize;
    _communicatorInstance.get()->sendDataToAClient(_serverEndpoint, networkData, offset, 10);
    std::free(networkData);
}

void ClientRoom::_disconectionProcess()
{
    _communicatorInstance.get()->sendDataToAClient(_serverEndpoint, nullptr, 0, 13);
}

void ClientRoom::_startConnexionProtocol()
{
    unsigned short pseudoSize = _pseudo.size();
    unsigned short passwordSize = _password.size();
    void *networkData = std::malloc(sizeof(char) * (pseudoSize + passwordSize) + sizeof(unsigned short) * 2);
    unsigned short offset = 0;

    if (networkData == nullptr)
        throw MallocError("Malloc failed.");
    std::memcpy(networkData, &pseudoSize, sizeof(unsigned short));
    offset += sizeof(unsigned short);
    std::memcpy((void *)((char *)networkData + offset), _pseudo.c_str(), sizeof(char) * pseudoSize);
    offset += sizeof(char) * pseudoSize;
    std::memcpy((void *)((char *)networkData + offset), &passwordSize, sizeof(unsigned short));
    offset += sizeof(unsigned short);
    std::memcpy((void *)((char *)networkData + offset), _password.c_str(), sizeof(char) * passwordSize);
    offset += sizeof(char) * passwordSize;
    _communicatorInstance.get()->startReceiverListening();
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
}

void ClientRoom::_holdADisconnectionRequest()
{
    std::vector<std::shared_ptr<Entity>> entity = _worldInstance->joinEntities<Enemy>();
    for (auto &it : entity) {
        _worldInstance->removeEntity(it->getId());
    }
    entity = _worldInstance->joinEntities<EnemyProjectile>();
    for (auto &it : entity) {
        _worldInstance->removeEntity(it->getId());
    }
    entity = _worldInstance->joinEntities<ParallaxBackground>();
    for (auto &it : entity) {
        _worldInstance->removeEntity(it->getId());
    }
    entity = _worldInstance->joinEntities<Player>();
    for (auto &it : entity) {
        _worldInstance->removeEntity(it->getId());
    }
    entity = _worldInstance->joinEntities<AlliedProjectile>();
    for (auto &it : entity) {
        _worldInstance->removeEntity(it->getId());
    }
    _disconectionProcess();
    _worldInstance->getResource<MenuStates>().currentState = MenuStates::MAIN_MENU;
}

void ClientRoom::_protocol15Answer(CommunicatorMessage connectionResponse)
{
    unsigned short roomNumber = 0;
    std::size_t offset = sizeof(unsigned short);
    sf::Vector2u windowSize = _worldInstance->getResource<RenderWindowResource>().window.getSize();

    std::memcpy(&roomNumber, connectionResponse.message.data, sizeof(unsigned short));
    for (int i = 0; i < roomNumber; i++) {
        unsigned short roomId = 0;
        unsigned short nameSize = 0;
        std::memcpy(&roomId, (void *)((char *)connectionResponse.message.data + offset), sizeof(unsigned short));
        offset += sizeof(unsigned short);
        std::memcpy(&nameSize, (void *)((char *)connectionResponse.message.data + offset), sizeof(unsigned short));
        offset += sizeof(unsigned short);
        char *tempRoomName = (char *)connectionResponse.message.data + offset;
        std::string roomName = std::to_string(roomId);
        roomName.append("- ");
        roomName.append(tempRoomName, nameSize);
        offset += sizeof(char) * nameSize;
        createNewButton(*(_worldInstance.get()), windowSize.x / 2 - 100, i * 60, 200, 50,
            ButtonActionMap::CONNECT_TO_ROOM, LayerLvL::BUTTON, MenuStates::LOBBY, roomName);
    }
    if (roomNumber != 0)
        createNewButton(*(_worldInstance.get()), 100, 200, 200, 50, ButtonActionMap::MATCHMAKED_ROOM, LayerLvL::BUTTON,
            MenuStates::LOBBY, "Matchmaked Join");
}

bool ClientRoom::_answerProtocols()
{
    CommunicatorMessage connectionOperation;

    try {
        connectionOperation = _communicatorInstance.get()->getLastMessage();
        if (connectionOperation.message.type == 11) {
            std::cerr << "No places left inside the hub. Please retry later" << std::endl;
            goToMainMenu(*(_worldInstance.get()), *(_worldInstance->joinEntities<Button>().at(0).get()));
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
            _updateEcsData();
        }
        if (connectionOperation.message.type == 50) {
            if (_state == ClientState::RUN)
                _holdAChatRequest(connectionOperation);
        }
    } catch (NetworkError &error) {
    }
    return true;
}

void ClientRoom::_initSoloData(void)
{
    createNewPlayer(*_worldInstance.get(), 20, 500, 0, 0, 1, 102, 102, 100, 10, 4, true, 1, _pseudo);
}

int ClientRoom::startGame()
{
    UserConnection connection;

    try {
        connection.userConnection();
    } catch (error_lib::RTypeError &e) {
        std::cerr << e.what() << std::endl;
        return (84);
    }
    _pseudo = connection.getPseudo();
    _password = connection.getPassword();
    connection.~UserConnection();
    _startLoop();
    return (0);
}

void ClientRoom::_startLoop()
{
    std::signal(SIGINT, signalCallbackHandler);
    MenuStates::menuState_e currentMenuStates = MenuStates::UNDEFINED;

    _oldMenuStates = MenuStates::UNDEFINED;
    isMenuUpdated = true;
    _startConnexionProtocol();
    _state = ClientRoom::RUN;
    while (_state != ClientState::ENDED) {
        if (isMenuUpdated)
            _updateEcsData();
        currentMenuStates = _worldInstance->getResource<MenuStates>().currentState;
        _oldMenuStates = currentMenuStates;
        if (currentMenuStates != MenuStates::MAIN_MENU && currentMenuStates != MenuStates::SOLO_GAME
            && (currentMenuStates != MenuStates::SOLO_GAME && getPreviousMenu() != MenuStates::SOLO_GAME)) {
            if (!_answerProtocols())
                return;
        }
        _worldInstance->runSystems();
        if (_oldMenuStates != _worldInstance->getResource<MenuStates>().currentState)
            isMenuUpdated = true;
    }
    _disconectionProcess();
}

void ClientRoom::_updateEcsResources()
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
        _loadButtonActionMap();
    if (_worldInstance->containsResource<MusicResource>()) {
        _worldInstance->getResource<MusicResource>().addMusic(
            graphicECS::SFML::Resources::MusicResource::BACKGROUNDTHEME, BACKGROUND_MUSIC_1);
    }
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

void ClientRoom::_loadButtonActionMap()
{
    ButtonActionMap &actionsList = _worldInstance->getResource<ButtonActionMap>();

    actionsList.addAction(ButtonActionMap::PAUSE, std::function<void(World &, Entity &)>(pauseGame));
    actionsList.addAction(ButtonActionMap::RESUME, std::function<void(World &, Entity &)>(resumeGame));
    actionsList.addAction(ButtonActionMap::QUIT, std::function<void(World &, Entity &)>(exitWindow));
    actionsList.addAction(ButtonActionMap::WRITABLE, std::function<void(World &, Entity &)>(selectAWritable));
    actionsList.addAction(
        ButtonActionMap::WRITABLE_BUTTON, std::function<void(World &, Entity &)>(writableButtonAction));
    actionsList.addAction(ButtonActionMap::GO_MAIN_MENU, std::function<void(World &, Entity &)>(goToMainMenu));
    actionsList.addAction(ButtonActionMap::GO_LOBBY, std::function<void(World &, Entity &)>(goToLobby));
    actionsList.addAction(ButtonActionMap::CONNECT_TO_ROOM, std::function<void(World &, Entity &)>(connectToARoom));
    actionsList.addAction(ButtonActionMap::MATCHMAKED_ROOM, std::function<void(World &, Entity &)>(connectMatchmaked));
    actionsList.addAction(ButtonActionMap::GO_SOLO_GAME, std::function<void(World &, Entity &)>(launchSoloGame));
    actionsList.addAction(ButtonActionMap::SWITCH_MUSIC, std::function<void(World &, Entity &)>(switchMusic));
    actionsList.addAction(ButtonActionMap::SWITCH_SOUND, std::function<void(World &, Entity &)>(switchSound));
    actionsList.addAction(ButtonActionMap::GO_OPTION, std::function<void(World & world, Entity &)>(goOption));
}

void ClientRoom::_initLobbyButtons()
{
    sf::Vector2u windowSize = _worldInstance->getResource<RenderWindowResource>().window.getSize();

    std::size_t roomNameId =
        createNewWritable(*(_worldInstance.get()), windowSize.x - 300, 100, 200, 50, MenuStates::LOBBY);
    _worldInstance->getEntity(roomNameId).getComponent<WritableContent>().content = "Room Name";
    std::size_t playerNumberId =
        createNewWritable(*(_worldInstance.get()), windowSize.x - 300, 200, 200, 50, MenuStates::LOBBY);
    _worldInstance->getEntity(playerNumberId).getComponent<WritableContent>().content = "Player Number";
    std::size_t playerVelocityId =
        createNewWritable(*(_worldInstance.get()), windowSize.x - 300, 300, 200, 50, MenuStates::LOBBY);
    _worldInstance->getEntity(playerVelocityId).getComponent<WritableContent>().content = "Player Velocity";
    std::size_t enemyVelocityId =
        createNewWritable(*(_worldInstance.get()), windowSize.x - 300, 400, 200, 50, MenuStates::LOBBY);
    _worldInstance->getEntity(enemyVelocityId).getComponent<WritableContent>().content = "Enemy Velocity";

    std::size_t id = createNewWritableButton(*(_worldInstance.get()), windowSize.x - 300, 500, 200, 50,
        std::function<void(World &, Entity &, std::string &)>(createARoom), MenuStates::LOBBY, roomNameId);
    _worldInstance->getEntity(id).getComponent<graphicECS::SFML::Components::AssociatedId>().idList.push_back(
        playerNumberId);
    _worldInstance->getEntity(id).getComponent<graphicECS::SFML::Components::AssociatedId>().idList.push_back(
        playerVelocityId);
    _worldInstance->getEntity(id).getComponent<graphicECS::SFML::Components::AssociatedId>().idList.push_back(
        enemyVelocityId);
    createNewButton(*(_worldInstance.get()), 100, 100, 200, 50, ButtonActionMap::GO_MAIN_MENU, LayerLvL::BUTTON,
        MenuStates::LOBBY, "Back");
}

void ClientRoom::askForRooms()
{
    unsigned short pseudoSize = _pseudo.size();
    unsigned short passwordSize = _password.size();
    void *networkData = std::malloc(sizeof(char) * (pseudoSize + passwordSize) + sizeof(unsigned short) * 2);
    unsigned short offset = 0;

    if (networkData == nullptr)
        throw MallocError("Malloc failed.");
    std::memcpy(networkData, &pseudoSize, sizeof(unsigned short));
    offset += sizeof(unsigned short);
    std::memcpy((void *)((char *)networkData + offset), _pseudo.c_str(), sizeof(char) * pseudoSize);
    offset += sizeof(char) * pseudoSize;
    std::memcpy((void *)((char *)networkData + offset), &passwordSize, sizeof(unsigned short));
    offset += sizeof(unsigned short);
    std::memcpy((void *)((char *)networkData + offset), _password.c_str(), sizeof(char) * passwordSize);
    offset += sizeof(char) * passwordSize;
    _communicatorInstance.get()->sendDataToAClient(_serverEndpoint, networkData, offset, 14);
    std::free(networkData);
}

void ClientRoom::_initPausedButton()
{
    sf::Vector2u windowSize = _worldInstance->getResource<RenderWindowResource>().window.getSize();

    createNewButton(*(_worldInstance.get()), windowSize.x / 2 - 100, windowSize.y / 4 - 25, 200, 50,
        ButtonActionMap::RESUME, LayerLvL::BUTTON, MenuStates::PAUSED, "Resume");
    createNewButton(*(_worldInstance.get()), windowSize.x / 2 - 100, windowSize.y / 4 * 2 - 25, 200, 50,
        ButtonActionMap::GO_MAIN_MENU, LayerLvL::BUTTON, MenuStates::PAUSED, "Main menu");
    createNewButton(*(_worldInstance.get()), windowSize.x / 2 - 100, windowSize.y / 4 * 3 - 25, 200, 50,
        ButtonActionMap::QUIT, LayerLvL::BUTTON, MenuStates::PAUSED, "Exit");
}

void ClientRoom::_initOptionButton()
{
    sf::Vector2u windowSize = _worldInstance->getResource<RenderWindowResource>().window.getSize();

    createNewButton(*(_worldInstance.get()), windowSize.x / 2 - 100, windowSize.y / 4 - 25, 200, 50,
        ButtonActionMap::SWITCH_SOUND, LayerLvL::BUTTON, MenuStates::OPTION, "SOUND");
    createNewButton(*(_worldInstance.get()), windowSize.x / 2 - 100, windowSize.y / 4 * 2 - 25, 200, 50,
        ButtonActionMap::SWITCH_MUSIC, LayerLvL::BUTTON, MenuStates::OPTION, "MUSIC");
    createNewButton(*(_worldInstance.get()), windowSize.x / 2 - 100, windowSize.y / 4 * 3 - 25, 200, 50,
        ButtonActionMap::GO_MAIN_MENU, LayerLvL::BUTTON, MenuStates::OPTION, "BACK");
}

void ClientRoom::_updateEcsEntities()
{
    auto entities = _worldInstance->joinEntities<Button>();
    for (auto &it : entities) {
        _worldInstance->removeEntity(it->getId());
    }
    entities = _worldInstance->joinEntities<MusicComponent>();
    for (auto &it :entities) {
        it->getComponent<MusicComponent>()._status = sf::Music::Stopped;
    }
    entities = _worldInstance->joinEntities<SoundComponent>();
    for (auto &it : entities) {
        it->getComponent<SoundComponent>()._status = sf::Sound::Stopped;
    }
    if (_worldInstance
            ->joinEntities<MouseInputComponent, KeyboardInputComponent, ControllerButtonInputComponent,
                ControllerJoystickInputComponent, ActionQueueComponent, AllowMouseAndKeyboardComponent,
                AllowControllerComponent>()
            .empty())
        _initInputsEntity();
    if (_worldInstance->containsResource<MenuStates>()) {
        switch (_worldInstance->getResource<MenuStates>().currentState) {
            case MenuStates::MAIN_MENU:
                if (_oldMenuStates == MenuStates::PAUSED || _oldMenuStates == MenuStates::MULTI_GAME) {
                    try {
                        _communicatorInstance->replaceClientByAnother(_serverEndpoint, _highInstanceEndpoint);
                        _serverEndpoint = _highInstanceEndpoint;
                    } catch (NetworkError &e) {
                        std::cerr << "Network error: " << e.what() << std::endl;
                    }
                    _removeMultiSystems();
                    _removeSoloSystems();
                }
                if (_oldMenuStates == MenuStates::MULTI_GAME || _oldMenuStates == MenuStates::LOBBY) {
                    _removeMultiSystems();
                } else if (_oldMenuStates == MenuStates::SOLO_GAME) {
                    _removeSoloSystems();
                }
                _initMainMenuButtons();
                break;
            case MenuStates::LOBBY:
                askForRooms();
                _initLobbyButtons();
                break;
            case MenuStates::SOLO_GAME:
                if (_oldMenuStates != MenuStates::PAUSED)
                    _initSoloData();
                _initInGameButtons();
                _initInGameWritables();
                _initInGameBackgrounds();
                _initInGameText();
                break;
            case MenuStates::MULTI_GAME:
                if (_oldMenuStates == MenuStates::LOBBY) {
                    // _disconectionProcess();
                }
                _worldInstance->getResource<GameStates>().currentState = GameStates::IN_GAME;
                _initInGameButtons();
                _initInGameWritables();
                if (_worldInstance->joinEntities<ParallaxBackground>().empty()) {
                    _initInGameText();
                    _initInGameBackgrounds();
                }
                break;
            case MenuStates::PAUSED: _initPausedButton(); break;
            case MenuStates::OPTION: _initOptionButton(); break;
            default: break;
        }
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
    entity.getComponent<ControllerJoystickInputComponent>().controllerJoystickMapActions.emplace(
        std::make_pair<unsigned int, std::pair<ActionQueueComponent::inputAction_e, float>>(
            0, std::make_pair<ActionQueueComponent::inputAction_e, float>(ActionQueueComponent::MOVEX, 0)));
    entity.getComponent<ControllerButtonInputComponent>().controllerButtonMapActions.emplace(
        std::make_pair<unsigned int, std::pair<ActionQueueComponent::inputAction_e, float>>(
            0, std::make_pair<ActionQueueComponent::inputAction_e, float>(ActionQueueComponent::SHOOT, 10)));
    entity.getComponent<MouseInputComponent>().MouseMapActions.emplace(
        std::make_pair<sf::Mouse::Button, std::pair<ActionQueueComponent::inputAction_e, float>>(
            sf::Mouse::Button::Left,
            std::make_pair<ActionQueueComponent::inputAction_e, float>(ActionQueueComponent::BUTTON_CLICK, 0)));
}

void ClientRoom::_initInGameButtons()
{
    sf::Vector2u windowSize(0, 0);

    if (_worldInstance->containsResource<RenderWindowResource>())
        windowSize = _worldInstance->getResource<RenderWindowResource>().window.getSize();
    createNewButton(*(_worldInstance.get()), 0, 0, 68, 68, ButtonActionMap::PAUSE, LayerLvL::BUTTON,
        MenuStates::SOLO_GAME, "Pause");
    createNewButton(*(_worldInstance.get()), 0, 0, 68, 68, ButtonActionMap::PAUSE, LayerLvL::BUTTON,
        MenuStates::MULTI_GAME, "Pause");
}

void ClientRoom::_initInGameText()
{
    createNewText(*(_worldInstance.get()), 1700, 20, 16, LayerLvL::TEXT, MenuStates::MULTI_GAME, "Remaining Life : 0");
    createNewText(*(_worldInstance.get()), 1700, 20, 16, LayerLvL::TEXT, MenuStates::SOLO_GAME, "Remaining Life : 0");
}

void ClientRoom::_initMainMenuButtons()
{
    sf::Vector2u windowSize(0, 0);

    if (_worldInstance->containsResource<RenderWindowResource>())
        windowSize = _worldInstance->getResource<RenderWindowResource>().window.getSize();
    createNewButton(*(_worldInstance.get()), windowSize.x / 2 - 100, windowSize.y / 5 - 25, 200, 50,
        ButtonActionMap::GO_SOLO_GAME, LayerLvL::BUTTON, MenuStates::MAIN_MENU, "Solo");
    createNewButton(*(_worldInstance.get()), windowSize.x / 2 - 100, windowSize.y / 5 * 2 - 25, 200, 50,
        ButtonActionMap::GO_LOBBY, LayerLvL::BUTTON, MenuStates::MAIN_MENU, "Lobby");
    createNewButton(*(_worldInstance.get()), windowSize.x / 2 - 100, windowSize.y / 5 * 3 - 25, 200, 50,
        ButtonActionMap::GO_OPTION, LayerLvL::BUTTON, MenuStates::MAIN_MENU, "Option");
    createNewButton(*(_worldInstance.get()), windowSize.x / 2 - 100, windowSize.y / 5 * 4 - 25, 200, 50,
        ButtonActionMap::QUIT, LayerLvL::BUTTON, MenuStates::MAIN_MENU, "Quit");
}

void ClientRoom::_initInGameWritables()
{
    std::size_t writableIdMulti =
        createNewWritable(*(_worldInstance.get()), 1450, 900, 350, 50, MenuStates::MULTI_GAME);

    createNewWritableButton(*(_worldInstance.get()), 1820, 900, 80, 50,
        std::function<void(World &, Entity &, std::string &)>(publishNewChatMessage), MenuStates::MULTI_GAME,
        writableIdMulti);
}

void ClientRoom::_updateEcsSystems()
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
    if (!_worldInstance->containsSystem<UpdateLifeTextSystem>())
        _worldInstance->addSystem<UpdateLifeTextSystem>();
    if (_worldInstance->containsResource<MenuStates>()
        && _worldInstance->getResource<MenuStates>().currentState == MenuStates::SOLO_GAME) {
        if (!_worldInstance->containsSystem<MobGeneration>())
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
        if (!_worldInstance->containsSystem<ApplyInputDelay>())
            _worldInstance->addSystem<ApplyInputDelay>();
    } else if (_worldInstance->containsResource<MenuStates>()
        && _worldInstance->getResource<MenuStates>().currentState == MenuStates::LOBBY) {
        if (!_worldInstance->containsSystem<SendToServer>())
            _worldInstance->addSystem<SendToServer>();
        if (!_worldInstance->containsSystem<SendNewlyCreatedToServer>())
            _worldInstance->addSystem<SendNewlyCreatedToServer>();
    }
}

void ClientRoom::_removeMultiSystems()
{
    if (_worldInstance->containsSystem<SendToServer>())
        _worldInstance->removeSystem<SendToServer>();
    if (_worldInstance->containsSystem<SendNewlyCreatedToServer>())
        _worldInstance->removeSystem<SendNewlyCreatedToServer>();
}

void ClientRoom::_removeSoloSystems()
{
    if (_worldInstance->containsSystem<MobGeneration>())
        _worldInstance->removeSystem<MobGeneration>();
    if (_worldInstance->containsSystem<EnemiesPatterns>())
        _worldInstance->removeSystem<EnemiesPatterns>();
    if (_worldInstance->containsSystem<EnemyShootSystem>())
        _worldInstance->removeSystem<EnemyShootSystem>();
    if (_worldInstance->containsSystem<Collide>())
        _worldInstance->removeSystem<Collide>();
    if (_worldInstance->containsSystem<DeathLife>())
        _worldInstance->removeSystem<DeathLife>();
    if (_worldInstance->containsSystem<LifeTimeDeath>())
        _worldInstance->removeSystem<LifeTimeDeath>();
    if (_worldInstance->containsSystem<DecreaseLifeTime>())
        _worldInstance->removeSystem<DecreaseLifeTime>();
    if (_worldInstance->containsSystem<ApplyInputDelay>())
        _worldInstance->removeSystem<ApplyInputDelay>();
    if (_worldInstance->containsResource<GameLevel>())
        _worldInstance->removeResource<GameLevel>();
}

void ClientRoom::_updateEcsData()
{
    _updateEcsResources();
    _updateEcsEntities();
    _updateEcsSystems();
    isMenuUpdated = false;
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
