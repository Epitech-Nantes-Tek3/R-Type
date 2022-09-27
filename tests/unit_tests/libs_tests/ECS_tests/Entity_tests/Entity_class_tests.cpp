/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** Basic Test
*/

#include "Components/Component.hpp"
#include "Entity/Entity.hpp"
#include <criterion/criterion.h>
#include <iostream>

/// @file tests/unit_tests/libs_tests/ECS_tests/Entity_tests

struct Position : public ecs::Component
{
    int x;
    int y;

    Position(const int X, const int Y) : x(X), y(Y){};
};

struct Name : public ecs::Component
{
    const std::string name;

    Name(const std::string _name) : name(_name){};
};

/// @brief Create and check if an entity have the good id
Test(Entity, creation_and_getId)
{
    ecs::Entity *entity = new ecs::Entity(1);

    cr_assert_eq(1, entity->getId());
    delete entity;
}

/// @brief Compare two entities non-identical id
Test(Entity, compare_two_non_identical_entities)
{
    ecs::Entity *entity1 = new ecs::Entity(1);
    ecs::Entity *entity2 = new ecs::Entity(2);

    cr_assert_eq(false, entity1 == entity2);
    cr_assert_eq(true, entity1 != entity2);

    delete entity1;
    delete entity2;
}
