/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** MusicComponentTests
*/

#include <criterion/criterion.h>
#include "MusicComponent.hpp"
#include "MusicResource.hpp"

using namespace ecs;
using namespace graphicECS::SFML::Components;
using namespace graphicECS::SFML::Resources;

Test(MusicComponent, create_music_undefined)
{
    MusicComponent music;

    cr_assert_eq(0, music.music_e);
}

Test(MusicComponent, create_music_shoot)
{
    MusicComponent music(MusicResource::LEVEL_ONE_THEME);

    cr_assert_eq(MusicResource::LEVEL_ONE_THEME, music.music_e);
}
