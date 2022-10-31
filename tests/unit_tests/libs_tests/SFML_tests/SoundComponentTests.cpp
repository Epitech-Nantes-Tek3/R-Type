/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** SoundComponentTests
*/

#include <criterion/criterion.h>
#include "SoundComponent.hpp"
#include "SoundResource.hpp"

using namespace ecs;
using namespace graphicECS::SFML::Components;
using namespace graphicECS::SFML::Resources;

Test(SoundComponent, create_sound_undefined)
{
    SoundComponent sound;

    cr_assert_eq(0, sound.soundName);
}

Test(SoundComponent, create_sound_shoot)
{
    SoundComponent sound(SoundResource::SHOOT);

    cr_assert_eq(SoundResource::SHOOT, sound.soundName);
}