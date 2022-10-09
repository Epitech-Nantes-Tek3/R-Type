/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** CreateAllyProjectile_test
*/

#include <algorithm>
#include <iostream>
#include <criterion/criterion.h>
#include "World/World.hpp"
#include "CreateAllyProjectile.hpp"

using namespace ecs;

Test(CreateAllyProjectile_test, CreateAllyProjectile)
{
    World world(1);
    
    std::size_t ally = world.addEntity()
                            .addComponent<Position>(1, 1)
                            .addComponent<Damage>(10)
                            .addComponent<Velocity>(1, 1)
                            .getId();

    std::size_t id_new_entity = createNewAllyProjectile(world, world.getEntity(ally));
    
    cr_assert_eq(1, ally);
    cr_assert_eq(2, id_new_entity);
}
