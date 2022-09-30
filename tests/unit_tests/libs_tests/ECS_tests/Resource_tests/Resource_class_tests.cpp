/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** Resource_class_tests
*/

#include <filesystem>
#include <criterion/criterion.h>
#include "Resource/Resource.hpp"
#include "World/World.hpp"

class Timer : public ecs::Resource {
  public:
    int _timer;

    Timer(const int x) : _timer(x) {};
};

class Texture : public ecs::Resource {
  public:
    std::filesystem::path _path;

    Texture(const std::filesystem::path path) : _path(path) {};
};

/// @brief Create a World and add and get resource in the World
Test(Resource, add_and_get_resource_in_the_World)
{
    ecs::World *world = new ecs::World();

    world->addResource<Timer>(1);
    class Timer &timer = world->getResource<Timer>();
    cr_assert_eq(timer._timer, 1);

    delete world;
}

/// @brief Create an World and get a non-existing Resource
Test(Resource, get_non_existant_resource_in_the_World)
{
    ecs::World *world = new ecs::World();

    try {
        class Timer &pos = world->getResource<Timer>();
        (void)pos;
    } catch (std::logic_error &err) {
        cr_assert_str_eq(err.what(), "attempted to get a non-existent Resource");
        return;
    }
    cr_assert_eq(0, 1);
}

/// @brief Try to remove a Resource from the World
Test(Resource, remove_a_resource)
{
    ecs::World *world = new ecs::World();
    world->addResource<Timer>(1);
    world->removeResource<Timer>();

    try {
        class Timer &timer = world->getResource<Timer>();
        (void)timer;
    } catch (std::logic_error &err) {
        cr_assert_str_eq(err.what(), "attempted to get a non-existent Resource");
        return;
    }
    cr_assert_eq(0, 1);
}

/// @brief Try to remove a non-existing Resource from an World
Test(Resource, remove_a_non_existant_Resource)
{
    ecs::World *world = new ecs::World();

    try {
        world->removeResource<Timer>();
    } catch (std::logic_error &err) {
        cr_assert_str_eq(err.what(), "attempted to remove a non-existent Resource");
        return;
    }
    cr_assert_eq(0, 1);
}

/// @brief Check if the World have one good given Resource
Test(Resource, contains_one_good_resource)
{
    ecs::World *world = new ecs::World();
    world->addResource<Timer>(1);

    cr_assert_eq(true, world->contains<Timer>());
}

/// @brief Check if the World have one wrong given Resource
Test(Resource, contains_one_wrong_resource)
{
    ecs::World *world = new ecs::World();
    world->addResource<Timer>(1);

    cr_assert_eq(false, world->contains<Texture>());
}

/// @brief Check if the World have many given Resources
Test(Resource, contains_many_good_resources)
{
    ecs::World *world = new ecs::World();
    world->addResource<Timer>(1);
    world->addResource<Texture>("Lego");

    auto a = world->contains<Texture, Timer>();
    cr_assert_eq(true, a);
}

/// @brief Check if the World have many wrong given Resource
Test(Resource, contains_many_wrong_resources)
{
    ecs::World *world = new ecs::World();
    world->addResource<Timer>(1);

    auto a = world->contains<Texture, Timer>();
    cr_assert_eq(false, a);
}

/// @brief Check if the World have search only one Resource
Test(Resource, search_only_one_resources)
{
    ecs::World *world = new ecs::World();
    world->addResource<Timer>(1);
    world->addResource<Texture>("Lego");

    auto a = world->contains<Texture>();
    cr_assert_eq(true, a);
}
