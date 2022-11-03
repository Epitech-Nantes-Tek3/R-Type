/*
** EPITECH PROJECT, 2022
** R-Type [WSL : Ubuntu]
** File description:
** AnimationComponent
*/

#include <criterion/criterion.h>
#include "AnimationComponent.hpp"
#include "WritableContentComponent.hpp"

using namespace graphicECS::SFML::Components;

Test(WritableContentComponent, create_class)
{
    WritableContentComponent a;

    cr_assert_eq(1, 1);
}
