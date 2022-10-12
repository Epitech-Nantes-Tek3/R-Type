/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** GraphicsRectangleComponentTests
*/

#include <criterion/criterion.h>
#include "GraphicsRectangleComponent.hpp"

using namespace ecs;

Test(GraphicsRectangleComponent, test_create_class)
{
    GraphicsRectangleComponent a;

    (void)a;
    cr_assert_eq(1, 1);
}