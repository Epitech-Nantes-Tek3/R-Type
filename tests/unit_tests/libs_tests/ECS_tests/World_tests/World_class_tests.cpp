/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** Basic Test
*/

/// @file tests/unit_tests/libs_tests/ECS_tests/World_tests

#include <World/World.hpp>
#include <algorithm>
#include <criterion/criterion.h>

class Position : public ecs::Component {
  public:
    double x;
    double y;

    Position(const double X, const double Y) : x(X), y(Y){};
    Position(Position &old) : x(old.x), y(old.y){};

    Position &operator=(Position const &other)
    {
        if (this == &other)
            return *this;

        this->x = other.x;
        this->y = other.y;
        return *this;
    }
};

class Velocity : public ecs::Component {
  public:
    double x;
    double y;

    Velocity(const double X, const double Y) : x(X), y(Y){};
    Velocity(Velocity &old) : x(old.x), y(old.y){};
};

class Distinct : public ecs::Component {
  public:
    std::size_t id;

    Distinct(const std::size_t ID = 0) : id(ID){};
};

auto operator==(Distinct const &distinct, Distinct const &other) { return distinct.id == other.id; }
auto operator!=(Distinct const &distinct, Distinct const &other) { return distinct.id != other.id; }

class Hitbox : public ecs::Component {
  public:
    int hight;
    int length;

    Hitbox(const int H, const int L) : hight(H), length(L){};
    Hitbox(Hitbox &old) : hight(old.hight), length(old.length){};
};

struct Move : public ecs::System {
    void run(ecs::World &world) override final
    {
        std::vector<std::shared_ptr<ecs::Entity>> joined = world.joinEntities<Position, Velocity>();

        auto move = [](std::shared_ptr<ecs::Entity> entityPtr) {
            Position &pos = entityPtr.get()->getComponent<Position>();
            Velocity &vel = entityPtr.get()->getComponent<Velocity>();

            pos.x += vel.x;
            pos.y += vel.y;
        };

        std::for_each(joined.begin(), joined.end(), move);
    }
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

Test(World, test_system)
{
    ecs::World world(1);

    world.addEntity().addComponent<Position>(5, 10);
    world.addEntity().addComponent<Position>(57, 35).addComponent<Velocity>(0.5, 2.9);
    world.addEntity().addComponent<Velocity>(0.1, -0.1);
    world.addEntity().addComponent<Velocity>(-9, 1.4).addComponent<Position>(26, 62);
    world.addEntity().addComponent<Hitbox>(9, 4).addComponent<Position>(26, 62);
    world.addEntity().addComponent<Hitbox>(57, 35).addComponent<Velocity>(562, 785);

    world.addSystem<Move>();

    std::vector<std::shared_ptr<ecs::Entity>> joinedEntities1 = world.joinEntities<Position, Velocity>();
    cr_assert_eq(2, joinedEntities1.size());

    std::shared_ptr<ecs::Entity> entity1 = joinedEntities1.back();
    Position &pos1 = entity1.get()->getComponent<Position>();
    cr_assert_eq(4, entity1.get()->getId());
    cr_assert_eq(pos1.x, 26);
    cr_assert_eq(pos1.y, 62);

    joinedEntities1.pop_back();

    std::shared_ptr<ecs::Entity> entity12 = joinedEntities1.back();
    Position &pos12 = entity12.get()->getComponent<Position>();
    cr_assert_eq(2, entity12.get()->getId());
    cr_assert_eq(pos12.x, 57);
    cr_assert_eq(pos12.y, 35);

    world.runSystems();

    std::vector<std::shared_ptr<ecs::Entity>> joinedEntities2 = world.joinEntities<Position, Velocity>();
    cr_assert_eq(2, joinedEntities2.size());

    std::shared_ptr<ecs::Entity> entity2 = joinedEntities2.back();
    Position &pos2 = entity2.get()->getComponent<Position>();
    cr_assert_eq(4, entity2.get()->getId());
    cr_assert_eq(pos2.x, 17);
    cr_assert_eq(pos2.y, 63.4);

    joinedEntities2.pop_back();

    std::shared_ptr<ecs::Entity> entity22 = joinedEntities2.back();
    Position &pos22 = entity22.get()->getComponent<Position>();
    cr_assert_eq(2, entity22.get()->getId());
    cr_assert_eq(pos22.x, 57.5);
    cr_assert_eq(pos22.y, 37.9);
}

Test(World, test_updateComponentOfAnEntityFromGivenDistinctiveComponent)
{
    ecs::World world(1);

    world.addEntity().addComponent<Position>(5, 10).addComponent<Distinct>(1);
    world.addEntity().addComponent<Position>(57, 35).addComponent<Velocity>(0.5, 2.9);
    world.addEntity().addComponent<Velocity>(0.1, -0.1).addComponent<Distinct>(2);
    world.addEntity().addComponent<Velocity>(-9, 1.4).addComponent<Position>(26, 62);
    std::size_t id = world.addEntity().addComponent<Hitbox>(9, 4).addComponent<Position>(26, 62).addComponent<Distinct>(3).getId();
    world.addEntity().addComponent<Hitbox>(57, 35).addComponent<Velocity>(562, 785);

    Position &pos = world.getEntity(id).getComponent<Position>();

    world.updateComponentOfAnEntityFromGivenDistinctiveComponent<Distinct, Position>(Distinct(3), Position(100, 200));

    cr_assert_eq(100, pos.x);
    cr_assert_eq(200, pos.y);
}
