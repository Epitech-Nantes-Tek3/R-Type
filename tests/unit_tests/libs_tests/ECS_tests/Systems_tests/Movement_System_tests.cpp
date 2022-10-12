/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** Movement_System_tests
*/

#include <unistd.h>
#include <criterion/criterion.h>
#include "World/World.hpp"
#include "Entity/Entity.hpp"
#include "GameComponents/PositionComponent.hpp"
#include "GameComponents/VelocityComponent.hpp"
#include "GameComponents/SizeComponent.hpp"
#include "GameSystems/MouvementSystem.hpp"
#include "GameSharedResources/GameClock.hpp"

using namespace ecs;

Test(Movement_System, moove_a_position)
{
    World world(1);

    std::size_t id = world.addEntity().addComponent<Position>(10, 10).addComponent<Velocity>(1, 1).getId();

    world.addSystem<Movement>();
    world.addResource<GameClock>();

    Position pos1 = world.getEntity(id).getComponent<Position>();

    cr_assert_eq(10, pos1.x);
    cr_assert_eq(10, pos1.y);

    sleep(1);
    world.runSystems();

    pos1 = world.getEntity(id).getComponent<Position>();

    cr_assert_eq(11, pos1.x);
    cr_assert_eq(11, pos1.y);
}