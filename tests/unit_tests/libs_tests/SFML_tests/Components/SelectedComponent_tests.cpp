/*
** EPITECH PROJECT, 2022
** R-Type [WSL : Ubuntu]
** File description:
** AnimationComponent
*/

#include <criterion/criterion.h>
#include "AnimationComponent.hpp"
#include "SelectedComponent.hpp"

using namespace graphicECS::SFML::Components;

Test(SelectedComponent, create_class)
{
    SelectedComponent a;

    cr_assert_eq(1, 1);
}
