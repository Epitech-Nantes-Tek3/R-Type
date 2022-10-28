/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** AllowMouseAndKeyboardComponentTests
*/

#include <criterion/criterion.h>
#include "AllowMouseAndKeyboardComponent.hpp"

using namespace ecs;
using namespace graphicECS::SFML::Components;

Test(AllowMouseAndKeyboardComponent, test_class_constructor)
{
    AllowMouseAndKeyboardComponent a;
    (void)a;
    cr_assert_eq(42, 42);
}