/*
** EPITECH PROJECT, 2022
** Project
** File description:
** GameClock_resource_tests
*/

#include <chrono>
#include <thread>
#include <criterion/criterion.h>
#include "GameSharedResources/GameClock.hpp"
#include "World/World.hpp"

Test(GameClock, reset_clock_test)
{
    World world(1);

    world.addResource<GameClock>();
    GameClock &clock = world.getResource<GameClock>();
    std::this_thread::sleep_for(std::chrono::duration<int>(1));
    clock.resetClock();
    cr_assert_eq(clock.getElapsedTime() < 1.0, true);
}

Test(GameClock, elapsedTime_test)
{
    World world(1);

    world.addResource<GameClock>();
    GameClock &clock = world.getResource<GameClock>();
    std::this_thread::sleep_for(std::chrono::duration<int>(7));
    cr_assert_eq(clock.getElapsedTime() < 8.0, true);
    cr_assert_eq(6.0 < clock.getElapsedTime(), true);
}