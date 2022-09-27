/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** Basic Test
*/

#include <criterion/criterion.h>
#include "Entity/Entity.hpp"

/// @file tests/unit_tests/libs_tests/ECS_tests/Entity_tests

/// @brief Create and check if an entity have the good id
Test(Entity, creation_and_getId)
{
    ecs::Entity *entity = new ecs::Entity(1);

    cr_assert_eq(1, entity->getId());
    delete entity;
}
