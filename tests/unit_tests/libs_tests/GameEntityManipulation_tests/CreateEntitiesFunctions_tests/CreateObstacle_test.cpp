/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** CreateObstacle_test
*/


#include <criterion/criterion.h>
#include "World/World.hpp"
#include "CreateObstacle.hpp"

using namespace ecs;

Test(CreateObstacle_test, CreateObstacle)
{
    World world(1);

    std::size_t id_new_entity = createNewObstacle(world, 10, 120, 5);

    cr_assert_eq(1, id_new_entity);
}