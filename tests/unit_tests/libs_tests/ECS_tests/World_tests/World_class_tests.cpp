/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** Basic Test
*/

/// @file tests/unit_tests/libs_tests/ECS_tests/World_tests

#include <criterion/criterion.h>
#include <World/World.hpp>

class Position : public ecs::Component {
  public:
    int x;
    int y;

    Position(const int X, const int Y) : x(X), y(Y){};
    Position(Position &old) : x(old.x), y(old.y){};
};

Test(World, creation_and_getId)
{
    ecs::World world(2);

    cr_assert_eq(2, world.getId());
}

Test(World, add_and_get_an_entity)
{
    ecs::World world(2);

    std::size_t id = world.addEntity().addComponent<Position>(10, 20).getId();

    ecs::Entity &entity = world.getEntity(id);
    Position &pos = entity.getComponent<Position>();
    cr_assert_eq(pos.x, 10);
    cr_assert_eq(pos.y, 20);
}

Test(World, get_a_non_existant_entity)
{
    ecs::World world(2);

    try {
        ecs::Entity &ent = world.getEntity(1);
        (void)ent;
    } catch (std::logic_error &err) {
        cr_assert_str_eq(err.what(), "attempted to get a non-existent entity");
        return;
    }
    cr_assert_eq(0, 1);
}

Test(World, remove_a_non_existant_entity)
{
    ecs::World world(2);

    try {
        world.removeEntity(1);
    } catch (std::logic_error &err) {
        cr_assert_str_eq(err.what(), "attempted to remove a non-existent entity");
        return;
    }
    cr_assert_eq(0, 1);
}
