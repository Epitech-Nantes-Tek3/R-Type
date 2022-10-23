/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** CreateProjectile_test
*/

#include <criterion/criterion.h>
#include "World/World.hpp"
#include "R-TypeLogic/EntityManipulation/CreateEntitiesFunctions/CreateProjectile.hpp"

using namespace ecs;
using namespace rtypelogic::entitymanipulation;

Test(CreateProjectile_test, CreateAlliedProjectile)
{
    World world(1);

    std::size_t id_new_entity = createNewProjectile(world, 5, 5, 10, 10, 10);

    cr_assert_eq(1, id_new_entity);
}
