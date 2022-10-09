/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** CreateEnemy_test
*/

#include <algorithm>
#include <iostream>
#include <criterion/criterion.h>
#include "World/World.hpp"
#include "CreateEnemy.hpp"

using namespace ecs;

Test(CreateEnemy_test, CreateEnemy)
{
    World world(1);
    Position pos = {1, 1};
    Weight weight = 1;
    Size size = {10, 10};
    Life life = 10;
    Damage damage = 10;
    DamageRadius damageRadius = 10;

    std::size_t id_new_entity = createNewEnemy(world, pos, weight, size, life, damage, damageRadius);

    cr_assert_eq(1, id_new_entity);
}