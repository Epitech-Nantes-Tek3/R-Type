/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** ButtonAction
*/

#include "ButtonAction.hpp"
#include <csignal>
#include "Error/Error.hpp"
#include "GraphicECS/SFML/Components/AssociatedIdComponent.hpp"
#include "GraphicECS/SFML/Components/GraphicsTextComponent.hpp"
#include "GraphicECS/SFML/Components/ParallaxComponent.hpp"
#include "GraphicECS/SFML/Components/SelectedComponent.hpp"
#include "GraphicECS/SFML/Components/WritableButtonActionComponent.hpp"
#include "GraphicECS/SFML/Components/WritableContentComponent.hpp"
#include "GraphicECS/SFML/Resources/RenderWindowResource.hpp"
#include "TextureName.hpp"
#include "Transisthor/TransisthorECSLogic/Client/Components/NetworkServer.hpp"
#include "R-TypeLogic/EntityManipulation/ButtonManipulation/SharedResources/GameStates.hpp"
#include "R-TypeLogic/Global/Components/AlliedProjectileComponent.hpp"
#include "R-TypeLogic/Global/Components/ControlableComponent.hpp"
#include "R-TypeLogic/Global/Components/EnemyComponent.hpp"
#include "R-TypeLogic/Global/Components/EnemyProjectileComponent.hpp"
#include "R-TypeLogic/Global/Components/PlayerComponent.hpp"
#include "R-TypeLogic/Global/Components/TextComponent.hpp"
#include "GraphicECS/SFML/Resources/MusicResource.hpp"
#include "GraphicECS/SFML/Resources/SoundResource.hpp"

using namespace graphicECS::SFML::Resources;
using namespace graphicECS::SFML::Components;

void exitWindow(World &world, Entity &entityPtr)
{
    (void)entityPtr;
#ifdef __linux__
    (void)world;
    std::raise(SIGINT);
#elif _WIN32
    RenderWindowResource &resource = world.getResource<RenderWindowResource>();
    resource.window.close();
#endif
}

static MenuStates::menuState_e oldMenuState = MenuStates::UNDEFINED;

void pauseGame(World &world, Entity &entityPtr)
{
    auto &state = world.getResource<MenuStates>();
    auto guard = std::lock_guard(state);
    oldMenuState = state.currentState;
    state.currentState = MenuStates::PAUSED;
    auto &gameState = world.getResource<GameStates>();
    auto gameGuard = std::lock_guard(gameState);
    gameState.currentState = GameStates::IN_PAUSED;
    (void)entityPtr;
}

void resumeGame(World &world, Entity &entityPtr)
{
    auto &state = world.getResource<MenuStates>();
    auto guard = std::lock_guard(state);
    state.currentState = oldMenuState;
    auto &gameState = world.getResource<GameStates>();
    auto gameGuard = std::lock_guard(gameState);
    gameState.currentState = GameStates::IN_GAME;
    (void)entityPtr;
}

void selectAWritable(World &world, Entity &entityPtr)
{
    RenderWindowResource &resource = world.getResource<RenderWindowResource>();
    if (entityPtr.contains<Selected>()) {
        auto guardOld = std::lock_guard(entityPtr);
        entityPtr.removeComponent<Selected>();
        if (entityPtr.contains<TextureName>()) {
            entityPtr.getComponent<TextureName>().textureName = GraphicsTextureResource::WRITABLE;
        }
        auto &state = world.getResource<GameStates>();
        auto guard = std::lock_guard(state);
        state.currentState = GameStates::IN_GAME;
        resource.window.setKeyRepeatEnabled(false);
        return;
    }
    resource.window.setKeyRepeatEnabled(true);
    auto joined = world.joinEntities<Selected, WritableContent>();
    if (!joined.empty()) {
        auto guardOld = std::lock_guard(*(joined.at(0)));
        joined.at(0)->removeComponent<Selected>();
        if (joined.at(0)->contains<TextureName>())
            joined.at(0)->getComponent<TextureName>().textureName = GraphicsTextureResource::WRITABLE;
    }
    auto guardNew = std::lock_guard(entityPtr);
    entityPtr.addComponent<Selected>();
    if (entityPtr.contains<TextureName>()) {
        entityPtr.getComponent<TextureName>().textureName = GraphicsTextureResource::WRITABLE_SELECTED;
    }
    auto &state = world.getResource<GameStates>();
    auto guard = std::lock_guard(state);
    state.currentState = GameStates::IN_WRITING;
}

void writableButtonAction(World &world, Entity &entityPtr)
{
    if (!entityPtr.contains<AssociatedId>())
        return;
    auto &idList = entityPtr.getComponent<AssociatedId>().idList;
    if (idList.empty())
        return;
    auto &entity = world.getEntity(idList.at(0));
    std::string writableContent = entity.getComponent<WritableContent>().content;
    if (!writableContent.size())
        return;
    auto guard = std::lock_guard(entity);
    auto &writableContentComponent = entity.getComponent<WritableContent>();
    writableContentComponent.content = "";
    entity.getComponent<GraphicsTextComponent>().text.setString("");
    entityPtr.getComponent<WritableButtonAction>().actionToExecute(world, entityPtr, writableContent);
}

void publishNewChatMessage(World &world, Entity &entityPtr, std::string &message)
{
    std::vector<std::shared_ptr<ecs::Entity>> servers = world.joinEntities<ecs::NetworkServer>();
    std::vector<std::shared_ptr<ecs::Entity>> players = world.joinEntities<ecs::Controlable>();
    Communicator &communicator = world.getTransisthorBridge()->getCommunicatorInstance();

    (void)entityPtr;
    if (!servers.size() || !players.size())
        return;
    communicator.utilitarySendChatMessage(players.at(0)->getComponent<ecs::Player>().name, message,
        {servers.at(0)->getComponent<ecs::NetworkServer>().id});
}

void createARoom(World &world, Entity &entityPtr, std::string &message)
{
    (void)entityPtr;
    try {
        world.getTransisthorBridge()->getCommunicatorInstance().getServerEndpointId();
    } catch (error_lib::NetworkError &error) {
        world.getResource<MenuStates>().currentState = MenuStates::MAIN_MENU;
        std::cerr << "No server currently running" << std::endl;
        return;
    }
    if (!world.containsResource<MenuStates>() || message.size() < 4 || message.size() > 10)
        return;
    short configs[6] = {4, 1, 1, 1, 1, 1};
    world.getTransisthorBridge()->getCommunicatorInstance().utilitarySendRoomConfiguration(
        message, configs, world.getTransisthorBridge()->getCommunicatorInstance().getClientByHisId(0));
    std::vector<std::shared_ptr<Entity>> joined = world.joinEntities<Selected>();
    for (auto &it : joined) {
        it->removeComponent<Selected>();
    }
    world.getResource<MenuStates>().currentState = MenuStates::MULTI_GAME;
}

void connectToARoom(World &world, Entity &entityPtr)
{
    (void)entityPtr;
    if (!world.containsResource<MenuStates>())
        return;
    void *networkData = std::malloc(sizeof(unsigned short));

    if (networkData == nullptr)
        throw std::logic_error("Malloc failed.");
    std::string &roomName = entityPtr.getComponent<TextComponent>().text;
    std::size_t delimiterPos = roomName.find("-");
    std::string idString = roomName.substr(0, delimiterPos);
    unsigned short choosenRoomId = std::atoi(idString.c_str());

    std::memcpy(networkData, &choosenRoomId, sizeof(unsigned short));
    communicator_lib::Client _serverEndPoint =
        world.getTransisthorBridge()->getCommunicatorInstance().getClientByHisId(0);
    world.getTransisthorBridge()->getCommunicatorInstance().sendDataToAClient(
        _serverEndPoint, networkData, sizeof(unsigned short), 16);
    world.getResource<MenuStates>().currentState = MenuStates::MULTI_GAME;
}

void launchSoloGame(World &world, Entity &entityPtr)
{
    (void)entityPtr;
    world.getResource<MenuStates>().currentState = MenuStates::SOLO_GAME;
    oldMenuState = MenuStates::SOLO_GAME;
}

void goToLobby(World &world, Entity &entityPtr)
{
    (void)entityPtr;
    world.getResource<MenuStates>().currentState = MenuStates::LOBBY;
    oldMenuState = MenuStates::LOBBY;
}

void goToMainMenu(World &world, Entity &entityPtr)
{
    (void)entityPtr;
    if (world.getResource<MenuStates>().currentState == MenuStates::PAUSED && oldMenuState != MenuStates::SOLO_GAME) {
        communicator_lib::Client _serverEndPoint =
            world.getTransisthorBridge()->getCommunicatorInstance().getClientByHisId(0);
        world.getTransisthorBridge()->getCommunicatorInstance().sendDataToAClient(_serverEndPoint, nullptr, 0, 13);
    }
    std::vector<std::shared_ptr<Entity>> entity = world.joinEntities<Enemy>();
    for (auto &it : entity) {
        world.removeEntity(it->getId());
    }
    entity = world.joinEntities<EnemyProjectile>();
    for (auto &it : entity) {
        world.removeEntity(it->getId());
    }
    entity = world.joinEntities<ParallaxBackground>();
    for (auto &it : entity) {
        world.removeEntity(it->getId());
    }
    entity = world.joinEntities<Player>();
    for (auto &it : entity) {
        world.removeEntity(it->getId());
    }
    entity = world.joinEntities<AlliedProjectile>();
    for (auto &it : entity) {
        world.removeEntity(it->getId());
    }
    world.getResource<MenuStates>().currentState = MenuStates::MAIN_MENU;
}

MenuStates::menuState_e getPreviousMenu() { return (oldMenuState); }

void switchMusic(World &world, Entity &entityPtr)
{
    (void)entityPtr;
    bool &play = world.getResource<MusicResource>().playMusic;
    play = (play) ? false : true;
}

void switchSound(World &world, Entity &entityPtr)
{
    (void)entityPtr;
    bool &play = world.getResource<SoundResource>().playSound;
    play = (play) ? false : true;
}

void goOption(World &world, Entity &entityPtr)
{
    (void)entityPtr;
    world.getResource<MenuStates>().currentState = MenuStates::OPTION;
}
