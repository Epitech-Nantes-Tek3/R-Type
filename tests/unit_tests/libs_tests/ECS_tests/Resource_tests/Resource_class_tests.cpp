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
}

class Texture : public ecs::Resource {
  public:
    std::filesystem::path _path;
}

Test(Resource, add_resource_in_the_World)
{
    ecs::World *world = new ecs::World();
    world->addResource<Timer>(1);

    class Timer &timer = resource->getComponent<Timer>();
    cr_assert_eq(timer._timer, 1);

    delete world;
}

/// @brief Create an Resource and get a non-existing component
Test(Resource, get_non_existant_resource_in_the_World)
{
    ecs::World *world = new ecs::World();

    try {
        class Timer &pos = world->getComponent<Timer>();
        (void)pos;
    } catch (std::logic_error &err) {
        cr_assert_str_eq(err.what(), "attempted to get a non-existent Resource");
        return;
    }
    cr_assert_eq(0, 1);
}