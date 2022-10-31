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

Test(MusicComponent, create_music_undefined)
{
    MusicComponent music;

    cr_assert_eq(0, music.musicName);
}

Test(MusicComponent, create_music_shoot)
{
    MusicComponent music(MusicResource::COMBATTHEME);

    cr_assert_eq(MusicResource::COMBATTHEME, music.musicName);
}
