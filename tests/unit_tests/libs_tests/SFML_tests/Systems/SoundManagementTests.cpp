/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** SoundManagementTests
*/

#include <criterion/criterion.h>
#include "Entity/Entity.hpp"
#include "GraphicECS/SFML/Components/SoundName.hpp"
#include "GraphicECS/SFML/Resources/SoundResource.hpp"
#include "GraphicECS/SFML/Systems/SoundManagement.hpp"
#include "World/World.hpp"

using namespace graphicECS::SFML::Components;
using namespace graphicECS::SFML::Resources;
using namespace graphicECS::SFML::Systems;
using namespace ecs;

Test(SoundSystem, add_undefined_song)
{
    World world(1);
    size_t id = world.addEntity().addComponent<SoundName>().getId();
    world.addResource<SoundResource>(SoundResource::soundName_e::UNDEFINED, "test");

    world.addSystem<SoundManagement>();

    cr_assert_eq(1, world.getId());
    cr_assert_eq(1, int(id));
}

Test(SoundSystem, add_defined_song)
{
    World world(1);
    size_t id = world.addEntity().addComponent<SoundName>(SoundResource::soundName_e::SHOOT).getId();
    world.addResource<SoundResource>(SoundResource::soundName_e::SHOOT, "test");

    world.addSystem<SoundManagement>();

    cr_assert_eq(1, world.getId());
    cr_assert_eq(1, int(id));
}