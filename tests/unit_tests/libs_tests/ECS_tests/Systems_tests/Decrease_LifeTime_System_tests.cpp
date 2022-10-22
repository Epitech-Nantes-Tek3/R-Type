/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** Decrease_LifeTime_System_tests
*/

#include <criterion/criterion.h>
#include "Entity/Entity.hpp"
#include "World/World.hpp"
#include "R-TypeLogic/Components/DeathComponent.hpp"
#include "R-TypeLogic/EntityManipulation/CreateEntitiesFunctions/CreateProjectile.hpp"
#include "R-TypeLogic/Systems/DecreaseLifeTimeSystem.hpp"
#include "R-TypeLogic/Systems/UpdateClockSystem.hpp"

using namespace ecs;

Test(Decrease_LifeTime_System, decrease_all_life_time)
{
    World world(1);

    createNewProjectile(world, 10, 10, 1, 1, 10);
    world.addResource<GameClock>();

    world.addSystem<DecreaseLifeTime>();
    world.addSystem<UpdateClock>();

    world.runSystems();

    std::this_thread::sleep_for(std::chrono::duration<int>(1));

    world.runSystems();

    std::chrono::duration<double> lifeTime = world.getEntity(1).getComponent<LifeTime>().timeLeft;

    cr_assert_eq(lifeTime.count() < 4 && lifeTime.count() > 0, 1);
}

Test(Decrease_LifeTime_System, multiple_decrease_all_life_time)
{
    World world(1);

    createNewProjectile(world, 10, 10, 1, 1, 10);
    createNewProjectile(world, 10, 10, 1, 1, 10);

    world.addResource<GameClock>();

    world.addSystem<DecreaseLifeTime>();
    world.addSystem<UpdateClock>();

    world.runSystems();

    std::this_thread::sleep_for(std::chrono::duration<int>(1));

    world.runSystems();

    std::chrono::duration<double> lifeTime = world.getEntity(1).getComponent<LifeTime>().timeLeft;
    std::chrono::duration<double> lifeTime2 = world.getEntity(2).getComponent<LifeTime>().timeLeft;

    cr_assert_eq(lifeTime.count() < 4 && lifeTime.count() > 0, 1);
    cr_assert_eq(lifeTime2.count() < 4 && lifeTime2.count() > 0, 1);
}
