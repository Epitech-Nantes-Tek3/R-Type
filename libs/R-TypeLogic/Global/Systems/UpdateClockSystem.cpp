/*
** EPITECH PROJECT, 2022
** Project
** File description:
** UpdateClockSystem
*/

#include "UpdateClockSystem.hpp"
#include <chrono>
#include "R-TypeLogic/Global/Components/ShootingFrequencyComponent.hpp"
#include "R-TypeLogic/Global/SharedResources/GameClock.hpp"

using namespace ecs;

void UpdateClock::run(World &world)
{
    GameClock &clock = world.getResource<GameClock>();
    std::vector<std::shared_ptr<ecs::Entity>> joined = world.joinEntities<ShootingFrequency>();

    clock.resetClock();
    for (auto it : joined)
        updateAFrequencyComponent<ShootingFrequency>(clock, it);
}
