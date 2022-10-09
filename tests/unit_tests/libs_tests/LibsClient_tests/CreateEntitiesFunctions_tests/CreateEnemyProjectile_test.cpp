/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** CreateEnemyProjectile_test
*/

#include <algorithm>
#include <iostream>
#include <criterion/criterion.h>
#include "World/World.hpp"
#include "CreateEnemyProjectile.hpp"

using namespace ecs;

Test(CreateEnemyProjectile_test, CreateEnemyProjectile)
{
    World world(1);
    
    std::size_t enemy = world.addEntity()
                            .addComponent<Position>(1, 1)
                            .addComponent<Damage>(10)
                            .addComponent<Velocity>(1, 1)
                            .getId();

    std::size_t id_new_entity = createNewEnemyProjectile(world, world.getEntity(enemy));
    
    cr_assert_eq(1, enemy);
    cr_assert_eq(2, id_new_entity);
}