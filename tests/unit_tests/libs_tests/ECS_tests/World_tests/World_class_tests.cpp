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

class Velocity : public ecs::Component {
  public:
    float x;
    float y;

    Velocity(const float X, const float Y) : x(X), y(Y){};
    Velocity(Velocity &old) : x(old.x), y(old.y){};
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

Test(World, join_entities)
{
    ecs::World world(2);

    world.addEntity().addComponent<Position>(5, 10);
    world.addEntity().addComponent<Position>(57, 35).addComponent<Velocity>(0.5, 2.9);
    world.addEntity().addComponent<Velocity>(0.1, -0.1);
    world.addEntity().addComponent<Velocity>(-9, 1.4).addComponent<Position>(26, 62);

    std::vector<std::shared_ptr<ecs::Entity>> joinedEntities = world.joinEntities<Position>();
    cr_assert_eq(3, joinedEntities.size());

    std::shared_ptr<ecs::Entity> entity = joinedEntities.back();
    Position &pos = entity.get()->getComponent<Position>();
    cr_assert_eq(4, entity.get()->getId());
    cr_assert_eq(pos.x, 26);
    cr_assert_eq(pos.y, 62);

    joinedEntities.pop_back();

    std::shared_ptr<ecs::Entity> entity2 = joinedEntities.back();
    Position &pos2 = entity2.get()->getComponent<Position>();
    cr_assert_eq(2, entity2.get()->getId());
    cr_assert_eq(pos2.x, 57);
    cr_assert_eq(pos2.y, 35);

    joinedEntities.pop_back();

    std::shared_ptr<ecs::Entity> entity3 = joinedEntities.back();
    Position &pos3 = entity3.get()->getComponent<Position>();
    cr_assert_eq(1, entity3.get()->getId());
    cr_assert_eq(pos3.x, 5);
    cr_assert_eq(pos3.y, 10);
}
