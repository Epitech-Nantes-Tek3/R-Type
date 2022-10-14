/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** CreateBackGround_tests
*/

#include <criterion/criterion.h>
#include "World/World.hpp"
#include "GameEntityManipulation/CreateEntitiesFunctions/CreateBackground.hpp"

using namespace ecs;

Test(CreateBackGround_test, CreateBackGround)
{
    World world(1);

    std::size_t id_new_entity = createNewBackGround(world, 10, 10, 1, 10, 10, 1, 1);

    cr_assert_eq(1, id_new_entity);
}