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
    SoundName sound;

    cr_assert_eq(0, sound.soundName);
}

Test(SoundName, create_sound_shoot)
{
    SoundName sound(SoundResource::SHOOT);

    cr_assert_eq(SoundResource::SHOOT, sound.soundName);
}