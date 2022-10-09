/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** CreateObstacle_test
*/

#include <algorithm>
#include <iostream>
#include <criterion/criterion.h>
#include "World/World.hpp"
#include "CreateObstacle.hpp"

using namespace ecs;

Test(CreateObstacle_test, CreateObstacle)
{
    World world(1);
    Position pos = {1, 1};
    Damage damage = 10;

    std::size_t id_new_entity = createNewObstacle(world, pos, damage);

    cr_assert_eq(1, id_new_entity);
}