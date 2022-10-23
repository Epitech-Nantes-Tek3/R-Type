/*
** EPITECH PROJECT, 2022
** Project
** File description:
** UpdateClockSystem
*/

#include "UpdateClockSystem.hpp"
#include <chrono>
#include "R-TypeLogic/Global/SharedResources/GameClock.hpp"

using namespace ecs;

void UpdateClock::run(World &world)
{
    GameClock &clock = world.getResource<GameClock>();

    clock.resetClock();
}
