/*
** EPITECH PROJECT, 2022
** R-Type [WSL : Ubuntu]
** File description:
** WritableButtonActionComponent
*/

#include <criterion/criterion.h>
#include "WritableButtonActionComponent.hpp"

using namespace graphicECS::SFML::Components;

Test(WritableButtonAction, create_class)
{
    WritableButtonAction a;

    cr_assert_eq(1, 1);
}
