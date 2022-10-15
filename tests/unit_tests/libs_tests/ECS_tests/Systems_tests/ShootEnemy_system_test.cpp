/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** ShootEnemy_system_test
*/

#include <chrono>
#include <thread>
#include <criterion/criterion.h>
#include "GameComponents/EnemyProjectileComponent.hpp"
#include "GameEntityManipulation/CreateEntitiesFunctions/CreateEnemy.hpp"
#include "GameSharedResources/GameClock.hpp"
#include "GameSharedResources/Random.hpp"
#include "GameSystems/EnemyShootSystem.hpp"
#include "Transisthor/TransisthorECSLogic/Server/Resources/NetworkableIdGenerator.hpp"
#include "World/World.hpp"

using namespace ecs;

Test(EnemyShootSystem, shoot_one)
{
    World world(1);

    world.addResource<RandomDevice>();
    world.addResource<GameClock>();
    world.addResource<NetworkableIdGenerator>();
    world.addSystem<EnemyShootSystem>();

    createNewEnemy(world, 1400, 540, 0, 0, 5, 100, 10, 5, 10, 10, "", 15);

    std::this_thread::sleep_for(std::chrono::duration<int>(2));
    world.runSystems();

    cr_assert_eq(world.joinEntities<EnemyProjectile>().size(), 1);
}