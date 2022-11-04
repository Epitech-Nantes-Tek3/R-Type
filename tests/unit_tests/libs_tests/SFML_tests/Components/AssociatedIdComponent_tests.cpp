/*
** EPITECH PROJECT, 2022
** R-Type [WSL : Ubuntu]
** File description:
** AssociatedIdComponent
*/

#include <criterion/criterion.h>
#include "AssociatedIdComponent.hpp"

using namespace graphicECS::SFML::Components;

Test(AssociatedIdComponent, create_class)
{
    AssociatedIdComponent a;

    cr_assert_eq(1, 1);
}
