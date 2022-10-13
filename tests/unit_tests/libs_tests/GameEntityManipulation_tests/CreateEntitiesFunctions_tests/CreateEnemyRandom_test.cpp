/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** CreateEnemyRandom_test
*/

#include <criterion/criterion.h>
#include "World/World.hpp"
#include "GameSharedResources/Random.hpp"
#include "GameEntityManipulation/CreateEntitiesFunctions/CreateEnemy.hpp"

using namespace ecs;

Test(CreateEnemyRandom_test, CreateEnemy)
{
    World world(1);

    world.addResource<RandomDevice>();

    std::size_t id_new_entity = createNewEnemyRandom(world, 1, 1, 1, 5, 5, 100, 10, 5);

    cr_assert_eq(1, id_new_entity);
}