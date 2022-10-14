/*
** EPITECH PROJECT, 2022
** Project
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

using namespace ecs;

Test(EnemyGoRandom_System, move_randomly)
{
    World world(1);

    world.addResource<RandomDevice>();
    world.addResource<GameClock>();
    world.addSystem<EnemiesGoRandom>();

    std::size_t id = createNewEnemy(world, 1400, 540, 0, 0, 5, 100, 10, 5, 10, 10, "", 15);
    Position &pos = world.getEntity(id).getComponent<Position>();
    Destination dest = world.getEntity(id).getComponent<Destination>();
    int x = dest.x;
    int y = dest.y;

    world.runSystems();
    std::this_thread::sleep_for(std::chrono::duration<int>(1));
    world.addSystem<Movement>();
    world.runSystems();

    cr_assert_eq(x - 1 <= pos.x && pos.x <= x + 1, true);
    cr_assert_eq(y - 1 <= pos.y && pos.y <= y + 1, true);
}