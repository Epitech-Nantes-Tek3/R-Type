/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** AllowControllerComponentTests
*/

#include <criterion/criterion.h>
#include "AllowControllerComponent.hpp"

using namespace ecs;

Test(AllowControllerComponent, test_class_constructor)
{
    AllowControllerComponent a;
    cr_assert_eq(42, 42);
}