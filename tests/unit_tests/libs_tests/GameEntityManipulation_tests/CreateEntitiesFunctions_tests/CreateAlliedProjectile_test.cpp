/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** CreateAlliedProjectile_test
*/

#include <criterion/criterion.h>
#include "World/World.hpp"
#include "R-TypeLogic/EntityManipulation/CreateEntitiesFunctions/CreateAlliedProjectile.hpp"

using namespace ecs;

Test(CreateAlliedProjectile_test, CreateAlliedProjectile)
{
    World world(1);

    std::size_t allied = world.addEntity()
                             .addComponent<Networkable>(10)
                             .addComponent<Position>(1, 1)
                             .addComponent<Damage>(10)
                             .addComponent<Velocity>(1, 1)
                             .getId();

    std::size_t id_new_entity = createNewAlliedProjectile(world, world.getEntity(allied));

    cr_assert_eq(2, id_new_entity);
}
