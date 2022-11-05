/*
** EPITECH PROJECT, 2022
** Project
** File description:
** ButtonAction
*/

#include "ButtonAction.hpp"
#include <csignal>
#include "GraphicECS/SFML/Components/AssociatedIdComponent.hpp"
#include "GraphicECS/SFML/Components/GraphicsTextComponent.hpp"
#include "GraphicECS/SFML/Components/SelectedComponent.hpp"
#include "GraphicECS/SFML/Components/WritableButtonActionComponent.hpp"
#include "GraphicECS/SFML/Components/WritableContentComponent.hpp"
#include "GraphicECS/SFML/Resources/RenderWindowResource.hpp"
#include "TextureName.hpp"
#include "R-TypeLogic/EntityManipulation/ButtonManipulation/SharedResources/GameStates.hpp"
#include "R-TypeLogic/EntityManipulation/ButtonManipulation/SharedResources/MenuStates.hpp"

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

void pauseGame(World &world, Entity &entityPtr)
{
    auto &state = world.getResource<MenuStates>();
    auto guard = std::lock_guard(state);
    state.currentState = MenuStates::GAME_PAUSED;
    auto &gameState = world.getResource<GameStates>();
    auto gameGuard = std::lock_guard(gameState);
    gameState.currentState = GameStates::IN_PAUSED;
    (void)entityPtr;
}

void resumeGame(World &world, Entity &entityPtr)
{
    auto &state = world.getResource<MenuStates>();
    auto guard = std::lock_guard(state);
    state.currentState = MenuStates::IN_GAME;
    auto &gameState = world.getResource<GameStates>();
    auto gameGuard = std::lock_guard(gameState);
    gameState.currentState = GameStates::IN_GAME;
    (void)entityPtr;
}

void selectAWritable(World &world, Entity &entityPtr)
{
    RenderWindowResource &resource = world.getResource<RenderWindowResource>();
    if (entityPtr.contains<Selected>()) {
        entityPtr.removeComponent<Selected>();
        entityPtr.removeComponent<TextureName>();
        entityPtr.addComponent<TextureName>(GraphicsTextureResource::WRITABLE);
        auto &state = world.getResource<GameStates>();
        auto guard = std::lock_guard(state);
        state.currentState = GameStates::IN_GAME;
        resource.window.setKeyRepeatEnabled(false);
        return;
    }
    resource.window.setKeyRepeatEnabled(true);
    entityPtr.addComponent<Selected>();
    entityPtr.removeComponent<TextureName>();
    entityPtr.addComponent<TextureName>(GraphicsTextureResource::WRITABLE_SELECTED);
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
    std::string &writableContent = entity.getComponent<WritableContent>().content;
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
    (void)world;
    (void)entityPtr;
    (void)message;
}

void setPseudo(World &world, Entity &entity, std::string &pseudo)
{
    (void)world;
    (void)entity;
    (void)pseudo;
}

void setPassword(World &world, Entity &entity, std::string &password)
{
    (void)world;
    (void)entity;
    (void)password;
}
