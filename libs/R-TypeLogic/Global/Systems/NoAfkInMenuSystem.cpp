/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** NoAfkInMenuSystem
*/

#include "NoAfkInMenuSystem.hpp"
#include <mutex>
#include "R-TypeLogic/EntityManipulation/ButtonManipulation/SharedResources/GameStates.hpp"
#include "R-TypeLogic/Global/Components/VelocityComponent.hpp"
#include "R-TypeLogic/Global/SharedResources/GameClock.hpp"
#include "R-TypeLogic/Server/Components/AfkFrequencyComponent.hpp"

using namespace ecs;

void NoAfkInMenu::run(World &world)
{
    std::vector<std::shared_ptr<Entity>> joined = world.joinEntities<AfkFrequency>();

    GameStates &gameState = world.getResource<GameStates>();
    auto guard = std::lock_guard(gameState);
    GameStates::gameState_e currState = gameState.currentState;
    if (currState == GameStates::IN_GAME)
        return;
    auto updatePlayersInMenu = [&world](std::shared_ptr<Entity> entityPtr) {
        std::lock_guard(*entityPtr.get());
        GameClock &gameClock = world.getResource<GameClock>();
        AfkFrequency &freq = entityPtr->getComponent<AfkFrequency>();

        auto secondGuard = std::lock_guard(gameClock);
        double delta = freq.frequency.count() - gameClock.getElapsedTime();

        if (delta <= 5.0) {
            Velocity &vel = entityPtr.get()->getComponent<Velocity>();

            vel.modified = true;
        }
    };
    std::for_each(joined.begin(), joined.end(), updatePlayersInMenu);
}