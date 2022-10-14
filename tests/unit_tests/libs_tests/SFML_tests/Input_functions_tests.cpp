/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** Input_functions_tests
*/

#include <chrono>
#include <thread>
#include <criterion/criterion.h>
#include "Entity/Entity.hpp"
#include "GameComponents/PositionComponent.hpp"
#include "GameComponents/SizeComponent.hpp"
#include "GameSystems/MovementSystem.hpp"
#include "GameComponents/VelocityComponent.hpp"
#include "GameSharedResources/GameClock.hpp"
#include "SFMLSystems/InputManagement.hpp"
#include "World/World.hpp"

using namespace ecs;

Test(movePlayerX, Move_x_of_a_player)
{
    World world(1);
    InputManagement test;
    std::size_t id = world.addEntity().addComponent<Position>(10, 10).addComponent<Velocity>(0, 0).getId();

    world.addSystem<Movement>();
    world.addSystem<InputManagement>();
    world.addResource<GameClock>();

    world.runSystems();

    Position pos1 = world.getEntity(id).getComponent<Position>();

    cr_assert_eq(10, pos1.x);
    cr_assert_eq(10, pos1.y);

    std::this_thread::sleep_for(std::chrono::duration<int>(1));

    test.movePlayerX(world, 1.0);

    world.runSystems();

    pos1 = world.getEntity(id).getComponent<Position>();

    cr_assert_eq(11, pos1.x);
    cr_assert_eq(10, pos1.y);
}