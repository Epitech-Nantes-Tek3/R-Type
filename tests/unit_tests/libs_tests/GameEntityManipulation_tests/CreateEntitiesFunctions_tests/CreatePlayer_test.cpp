/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** CreatePlayer_test
*/

#include <criterion/criterion.h>
#include "World/World.hpp"
#include "GameEntityManipulation/CreateEntitiesFunctions/CreatePlayer.hpp"

using namespace ecs;

Test(CreatePlayer_test, CreatePlayer)
{
    World world(1);

    std::size_t id_new_entity = createNewPlayer(world, 50, 20, 1, 1, 1, 4, 4, 100, 10, 5, false);

    cr_assert_eq(1, id_new_entity);
}