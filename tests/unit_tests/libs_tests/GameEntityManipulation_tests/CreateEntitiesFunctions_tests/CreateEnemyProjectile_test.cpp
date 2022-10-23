/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** CreateEnemyProjectile_test
*/

#include <criterion/criterion.h>
#include "World/World.hpp"
#include "R-TypeLogic/EntityManipulation/CreateEntitiesFunctions/CreateEnemyProjectile.hpp"

using namespace ecs;
using namespace rtypelogic::entitymanipulation;

Test(CreateEnemyProjectile_test, CreateEnemyProjectile)
{
    World world(1);

    world.addEntity()
        .addComponent<Networkable>(10)
        .addComponent<Position>(1, 1)
        .addComponent<Damage>(10)
        .addComponent<Velocity>(1, 1)
        .getId();

    std::vector<std::shared_ptr<ecs::Entity>> joined = world.joinEntities<Damage>();

    std::size_t id_new_entity = createNewEnemyProjectile(world, joined.at(0));

    cr_assert_eq(2, id_new_entity);
}
