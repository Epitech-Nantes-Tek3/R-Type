/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** CreateProjectile_test
*/

#include <algorithm>
#include <iostream>
#include <criterion/criterion.h>
#include "World/World.hpp"
#include "CreateProjectile.hpp"

using namespace ecs;

Test(CreateProjectile_test, CreateAllyProjectile)
{
    World world(1);
    Position pos = {1, 1};
    Velocity velocity = {1, 1};
    Damage damage = 10;

    std::size_t id_new_entity = createNewProjectile(world, pos, velocity, damage);

    cr_assert_eq(1, id_new_entity);
}
