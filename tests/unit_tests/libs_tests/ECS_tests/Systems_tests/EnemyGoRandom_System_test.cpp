/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** EnemyGoRandom_System_test
*/

#include <chrono>
#include <thread>
#include <criterion/criterion.h>
#include "Entity/Entity.hpp"
#include "GameEntityManipulation/CreateEntitiesFunctions/CreateEnemy.hpp"
#include "GameSharedResources/GameClock.hpp"
#include "GameSharedResources/Random.hpp"
#include "GameSystems/EnemiesGoRandom.hpp"
#include "GameSystems/MovementSystem.hpp"
#include "World/World.hpp"


#include <iostream>

using namespace ecs;

Test(EnemyGoRandom_System, move_randomly)
{
    World world(1);

    world.addResource<RandomDevice>();
    world.addResource<GameClock>();
    world.addSystem<EnemiesGoRandom>();

    std::size_t id = createNewEnemy(world, 1400, 540, 0, 0, 5, 100, 10, 5, 10, 10, "", 15);
    Position &pos = world.getEntity(id).getComponent<Position>();
    int x = pos.x;
    int y = pos.y;

    world.runSystems();
    std::this_thread::sleep_for(std::chrono::duration<int>(5));
    world.addSystem<Movement>();
    world.runSystems();

    Position &newPos = world.getEntity(id).getComponent<Position>();

    cr_assert_eq(x != newPos.x && y != newPos.y, true);
}