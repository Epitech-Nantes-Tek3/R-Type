/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** AllowMouseAndKeyboardComponentTests
*/

#include <criterion/criterion.h>
#include "AllowMouseAndKeyboardComponent.hpp"

using namespace ecs;

Test(AllowMouseAndKeyboardComponent, test_class_constructor)
{
    AllowMouseAndKeyboardComponent a;
    cr_assert_eq(42, 42);
}