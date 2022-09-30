/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** Basic Test
*/

/// @file tests/unit_tests/libs_tests/ECS_tests/Entity_tests

#include <criterion/criterion.h>
#include "Component/Component.hpp"
#include "Entity/Entity.hpp"

class Position : public ecs::Component {
  public:
    int x;
    int y;

    Position(const int X, const int Y) : x(X), y(Y){};
    Position(Position &old) : x(old.x), y(old.y){};
};

class Name : public ecs::Component {
  public:
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

/// @brief Create an Entity and link a component on it
Test(Entity, add_and_get_component)
{
    ecs::Entity *entity = new ecs::Entity(1);

    entity->addComponent<Position>(10, 95);
    class Position &pos = entity->getComponent<Position>();
    cr_assert_eq(pos.x, 10);
    cr_assert_eq(pos.y, 95);

    delete entity;
}

/// @brief Create an Entity and get a non-existing component
Test(Entity, get_non_existant_component)
{
    ecs::Entity *entity = new ecs::Entity(1);

    try {
        class Position &pos = entity->getComponent<Position>();
        (void)pos;
    } catch (std::logic_error &err) {
        cr_assert_str_eq(err.what(), "attempted to get a non-existent component");
        return;
    }
    cr_assert_eq(0, 1);
}

/// @brief Try to remove a component from an Entity
Test(Entity, remove_a_component)
{
    ecs::Entity *entity = new ecs::Entity(1);
    entity->addComponent<Position>(10, 95);
    entity->removeComponent<Position>();

    try {
        class Position &pos = entity->getComponent<Position>();
        (void)pos;
    } catch (std::logic_error &err) {
        cr_assert_str_eq(err.what(), "attempted to get a non-existent component");
        return;
    }
    cr_assert_eq(0, 1);
}

/// @brief Try to remove a non-existing component from an Entity
Test(Entity, remove_a_non_existant_component)
{
    ecs::Entity *entity = new ecs::Entity(1);

    try {
        entity->removeComponent<Position>();
    } catch (std::logic_error &err) {
        cr_assert_str_eq(err.what(), "attempted to remove a non-existent component");
        return;
    }
    cr_assert_eq(0, 1);
}

/// @brief Check if an Entity have one given Component
Test(Entity, contains_one_good_component)
{
    ecs::Entity *entity = new ecs::Entity(1);
    entity->addComponent<Position>(10, 95);

    cr_assert_eq(true, entity->contains<Position>());
}

/// @brief Check if an Entity have one given Component
Test(Entity, contains_one_wrong_component)
{
    ecs::Entity *entity = new ecs::Entity(1);
    entity->addComponent<Position>(10, 95);

    cr_assert_eq(false, entity->contains<Name>());
}

/// @brief Check if an Entity have one given Component
Test(Entity, contains_many_good_components)
{
    ecs::Entity *entity = new ecs::Entity(1);
    entity->addComponent<Position>(10, 95);
    entity->addComponent<Name>("Casos");

    auto a = entity->contains<Name, Position>();
    cr_assert_eq(true, a);
}

/// @brief Check if an Entity have one given Component
Test(Entity, contains_many_wrong_components)
{
    ecs::Entity *entity = new ecs::Entity(1);
    entity->addComponent<Position>(10, 95);

    auto a = entity->contains<Name, Position>();
    cr_assert_eq(false, a);
}

/// @brief Check if an Entity have one given Component
Test(Entity, search_only_one_components)
{
    ecs::Entity *entity = new ecs::Entity(1);
    entity->addComponent<Position>(10, 95);
    entity->addComponent<Name>("Casos");

    auto a = entity->contains<Name>();
    cr_assert_eq(true, a);
}
