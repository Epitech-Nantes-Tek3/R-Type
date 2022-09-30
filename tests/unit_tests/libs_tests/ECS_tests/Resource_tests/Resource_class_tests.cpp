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
    Timer(Timer &old) : _timer(old._timer) {};
};

class Texture : public ecs::Resource {
  public:
    std::filesystem::path _path;

    Texture(const std::filesystem::path path) : _path(path) {};
};

Test(Resource, add_and_get_resource_in_the_World)
{
    ecs::World *world = new ecs::World();

    world->addResource<Timer>(1);
    class Timer &timer = world->getResource<Timer>();
    cr_assert_eq(timer._timer, 1);

    delete world;
}

/// @brief Create an Resource and get a non-existing Resource
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