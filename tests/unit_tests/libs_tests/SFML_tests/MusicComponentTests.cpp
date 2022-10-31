/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** MusicComponentTests
*/

#include <criterion/criterion.h>
#include "MusicName.hpp"
#include "MusicResource.hpp"

using namespace ecs;
using namespace graphicECS::SFML::Components;
using namespace graphicECS::SFML::Resources;

Test(MusicName, create_music_undefined)
{
    MusicName music;

    cr_assert_eq(0, music.musicName);
}

Test(MusicName, create_music_shoot)
{
    MusicName music(MusicResource::COMBATTHEME);

    cr_assert_eq(MusicResource::COMBATTHEME, music.musicName);
}
