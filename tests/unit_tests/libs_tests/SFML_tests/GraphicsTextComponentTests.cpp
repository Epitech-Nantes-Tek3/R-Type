/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** GraphicsTextComponentTests
*/

#include <criterion/criterion.h>
#include <GraphicsTextComponent.hpp>

using namespace ecs;

Test(GraphicsTextComponent, test_create_function)
{
    GraphicsTextComponent a;

    (void)a;
    cr_assert_eq(1, 1);
}