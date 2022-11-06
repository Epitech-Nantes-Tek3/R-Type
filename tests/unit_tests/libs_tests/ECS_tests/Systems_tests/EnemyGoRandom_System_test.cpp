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
#include "World/World.hpp"
#include "R-TypeLogic/EntityManipulation/CreateEntitiesFunctions/CreateEnemy.hpp"
#include "R-TypeLogic/Global/SharedResources/GameClock.hpp"
#include "R-TypeLogic/Global/SharedResources/Random.hpp"
#include "R-TypeLogic/Server/Systems/EnemiesPatterns.hpp"
#include "R-TypeLogic/Global/Systems/MovementSystem.hpp"
#include "R-TypeLogic/Global/Systems/UpdateClockSystem.hpp"

using namespace ecs;

Test(EnemyGoRandom_System, move_randomly_rollback)
{
    World world(1);

    world.addResource<RandomDevice>();
    world.addResource<GameClock>();
    world.addSystem<EnemiesPatterns>();
    world.addSystem<UpdateClock>();

    std::size_t id = createNewEnemy(world, 1400, 540, 0, 0, 5, 100, 10, 5, 10, 10, Enemy::BASIC,"", 15);
    Position &pos = world.getEntity(id).getComponent<Position>();
    int x = pos.x;
    int y = pos.y;

    world.runSystems();
    std::this_thread::sleep_for(std::chrono::duration<int>(5));;
    world.runSystems();

    Position &newPos = world.getEntity(id).getComponent<Position>();

    cr_assert_eq(x == newPos.x && y == newPos.y, true);
}

Test(EnemyGoRandom_System, move_randomly)
{
    World world(1);

    world.addResource<RandomDevice>();
    world.addResource<GameClock>();
    world.addSystem<EnemiesPatterns>();
    world.addSystem<UpdateClock>();

    std::size_t id = createNewEnemy(world, 1400, 540, 0, 0, 5, 100, 10, 5, 10, 10, Enemy::BASIC, "", 15);
    Position &pos = world.getEntity(id).getComponent<Position>();
    int x = pos.x;
    int y = pos.y;

    world.runSystems();
    std::this_thread::sleep_for(std::chrono::duration<double>(0.5));
    world.addSystem<Movement>();
    world.runSystems();

    Position &newPos = world.getEntity(id).getComponent<Position>();

    cr_assert_eq(x != newPos.x && y != newPos.y, true);
}

