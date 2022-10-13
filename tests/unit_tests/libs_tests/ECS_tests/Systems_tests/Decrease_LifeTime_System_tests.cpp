/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** Decrease_LifeTime_System_tests
*/

#include <criterion/criterion.h>
#include "Entity/Entity.hpp"
#include "GameComponents/DeathComponent.hpp"
#include "GameEntityManipulation/CreateEntitiesFunctions/CreateProjectile.hpp"
#include "GameSystems/DecreaseLifeTimeSystem.hpp"
#include "World/World.hpp"

using namespace ecs;

Test(Decrease_LifeTime_System, decrease_all_life_time)
{
    World world(1);

    createNewProjectile(world, 10, 10, 1, 1, 10);

    world.addSystem<DecreaseLifeTime>();

    for (int i = 0; i < 100; i++)
        world.runSystems();

    std::chrono::duration<double> LifeTime = world.getEntity(1).getComponent<LifeTime>().timeLeft;

    cr_assert_eq(0, LifeTime.count());
}

Test(Decrease_LifeTime_System, multiple_decrease_all_life_time)
{
    World world(1);

    createNewProjectile(world, 10, 10, 1, 1, 10);
    createNewProjectile(world, 10, 10, 1, 1, 10);

    world.addSystem<DecreaseLifeTime>();

    for (int i = 0; i < 100; i++)
        world.runSystems();

    std::chrono::duration<double> LifeTime = world.getEntity(1).getComponent<LifeTime>().timeLeft;
    std::chrono::duration<double> LifeTime2 = world.getEntity(2).getComponent<LifeTime>().timeLeft;

    cr_assert_eq(0, LifeTime.count());
    cr_assert_eq(0, LifeTime2.count());
}
