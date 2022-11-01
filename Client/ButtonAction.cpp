/*
** EPITECH PROJECT, 2022
** Project
** File description:
** ButtonAction
*/

#include "ButtonAction.hpp"
#include <csignal>
#include "GraphicECS/SFML/Components/SelectedComponent.hpp"
#include "GraphicECS/SFML/Resources/RenderWindowResource.hpp"
#include "TextureName.hpp"
#include "R-TypeLogic/EntityManipulation/ButtonManipulation/SharedResources/MenuStates.hpp"
#include "R-TypeLogic/EntityManipulation/ButtonManipulation/SharedResources/GameStates.hpp"

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
    (void)world;
    if (entityPtr.contains<Selected>()) {
        entityPtr.removeComponent<Selected>();
        entityPtr.removeComponent<TextureName>();
        entityPtr.addComponent<TextureName>(GraphicsTextureResource::WRITABLE);
        auto &state = world.getResource<GameStates>();
        auto guard = std::lock_guard(state);
        state.currentState = GameStates::IN_GAME;
        return;
    }
    entityPtr.addComponent<Selected>();
    entityPtr.removeComponent<TextureName>();
    entityPtr.addComponent<TextureName>(GraphicsTextureResource::WRITABLE_SELECTED);
    auto &state = world.getResource<GameStates>();
    auto guard = std::lock_guard(state);
    state.currentState = GameStates::IN_WRITING;
}