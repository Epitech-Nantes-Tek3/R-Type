/*
** EPITECH PROJECT, 2022
** Project
** File description:
** ButtonAction
*/

#include "ButtonAction.hpp"
#include <csignal>
#include "GraphicECS/SFML/Resources/RenderWindowResource.hpp"
#include "R-TypeLogic/EntityManipulation/ButtonManipulation/SharedResources/MenuStates.hpp"

using namespace graphicECS::SFML::Resources;

void exitWindow(World &world)
{
#ifdef __linux__
    (void)world;
    std::raise(SIGINT);
#elif _WIN32
    RenderWindowResource &resource = world.getResource<RenderWindowResource>();
    resource.window.close();
#endif
}

void pauseGame(World &world)
{
    auto &state = world.getResource<MenuStates>();
    auto guard = std::lock_guard(state);
    state.currentState = MenuStates::GAME_PAUSED;
}

void resumeGame(World &world)
{
    auto &state = world.getResource<MenuStates>();
    auto guard = std::lock_guard(state);
    state.currentState = MenuStates::IN_GAME;
}