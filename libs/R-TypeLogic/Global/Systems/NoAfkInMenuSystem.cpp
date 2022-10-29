/*
** EPITECH PROJECT, 2022
** Project
** File description:
** NoAfkInMenuSystem
*/

#include "NoAfkInMenuSystem.hpp"
#include "R-TypeLogic/EntityManipulation/ButtonManipulation/SharedResources/MenuStates.hpp"
#include "R-TypeLogic/Global/Components/VelocityComponent.hpp"
#include "R-TypeLogic/Global/SharedResources/GameClock.hpp"
#include "R-TypeLogic/Server/Components/AfkFrequencyComponent.hpp"

using namespace ecs;

void NoAfkInMenu::run(World &world)
{
    std::vector<std::shared_ptr<Entity>> joined = world.joinEntities<AfkFrequency>();

    if (world.getResource<MenuStates>().currentState == MenuStates::IN_GAME)
        return;

    auto updatePlayersInMenu = [&world](std::shared_ptr<Entity> entityPtr) {
        std::lock_guard(*entityPtr.get());
        GameClock &gameClock = world.getResource<GameClock>();
        AfkFrequency &freq = entityPtr->getComponent<AfkFrequency>();

        double delta = freq.frequency.count() - gameClock.getElapsedTime();

        if (delta <= 5.0) {
            Velocity &vel = entityPtr.get()->getComponent<Velocity>();

            vel.modified = true;
        }
    };
    std::for_each(joined.begin(), joined.end(), updatePlayersInMenu);
}