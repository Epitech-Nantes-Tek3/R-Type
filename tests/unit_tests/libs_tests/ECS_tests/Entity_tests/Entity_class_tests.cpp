/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** Basic Test
*/

#include <criterion/criterion.h>
#include "Entity/Entity.hpp"

/// @file tests/unit_tests/libs_tests/ECS_tests/Entity_tests

/// @brief Very Basic Test
Test(Basic, some_basics_tests)
{
    cr_assert_eq(42, 42);
}
