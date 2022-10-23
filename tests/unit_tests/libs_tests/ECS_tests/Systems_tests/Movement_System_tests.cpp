/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** Movement_System_tests
*/

#include <chrono>
#include <thread>
#include <criterion/criterion.h>
#include "Entity/Entity.hpp"
#include "World/World.hpp"
#include "R-TypeLogic/Global/Components/PositionComponent.hpp"
#include "R-TypeLogic/Global/Components/SizeComponent.hpp"
#include "R-TypeLogic/Global/Components/VelocityComponent.hpp"
#include "R-TypeLogic/Global/SharedResources/GameClock.hpp"
#include "R-TypeLogic/Global/Systems/MovementSystem.hpp"
#include "R-TypeLogic/Global/Systems/UpdateClockSystem.hpp"

using namespace ecs;
using namespace rtypelogic::global;

Test(Movement_System, moove_a_position)
{
    World world(1);

    std::size_t id = world.addEntity().addComponent<Position>(10, 10).addComponent<Velocity>(1, 1).getId();

    world.addSystem<Movement>();
    world.addSystem<UpdateClock>();
    world.addResource<GameClock>();

    Position pos1 = world.getEntity(id).getComponent<Position>();

    cr_assert_eq(10, pos1.x);
    cr_assert_eq(10, pos1.y);

    std::this_thread::sleep_for(std::chrono::duration<int>(1));
    world.runSystems();

    pos1 = world.getEntity(id).getComponent<Position>();

    cr_assert_eq(11, (int)pos1.x);
    cr_assert_eq(11, (int)pos1.y);
}
