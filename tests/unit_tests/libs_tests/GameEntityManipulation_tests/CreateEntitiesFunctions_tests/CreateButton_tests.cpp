/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** CreateButton_tests
*/

#include <criterion/criterion.h>
#include "World/World.hpp"
#include "R-TypeLogic/EntityManipulation/CreateEntitiesFunctions/CreateButton.hpp"

using namespace ecs;

Test(CreateButton_test, CreateButton)
{
    World world(1);

    std::size_t id_new_entity = createNewButton(world, 10, 10, 1, 10, 10, 1, 1);

    cr_assert_eq(1, id_new_entity);
}
