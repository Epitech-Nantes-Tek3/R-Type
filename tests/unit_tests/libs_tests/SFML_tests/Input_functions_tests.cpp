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
#include "SFMLSystems/InputManagement.hpp"
#include "World/World.hpp"
#include "R-TypeLogic/Global/Components/PositionComponent.hpp"
#include "R-TypeLogic/Global/Components/SizeComponent.hpp"
#include "R-TypeLogic/Global/Components/VelocityComponent.hpp"
#include "R-TypeLogic/Global/SharedResources/GameClock.hpp"
#include "R-TypeLogic/Global/Systems/MovementSystem.hpp"

using namespace ecs;
using namespace graphicECS::SFML::Components;

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
