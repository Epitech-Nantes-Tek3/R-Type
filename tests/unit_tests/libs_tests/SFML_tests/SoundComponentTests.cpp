/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** SoundComponentTests
*/

#include <criterion/criterion.h>
#include "SoundName.hpp"
#include "SoundResource.hpp"

using namespace ecs;
using namespace graphicECS::SFML::Components;

Test(SoundName, create_sound_undefined)
{
    graphicECS::SFML::Components::SoundName sound;

    cr_assert_eq(0, sound.soundName);
}

Test(SoundName, create_sound_shoot)
{
    graphicECS::SFML::Components::SoundName sound(graphicECS::SFML::Resources::SoundResource::SHOOT);

    cr_assert_eq(graphicECS::SFML::Resources::SoundResource::SHOOT, sound.soundName);
}