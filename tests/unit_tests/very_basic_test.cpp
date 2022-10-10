/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** Basic Test
*/

#include <criterion/criterion.h>

/// @brief Very Basic Test
Test(Basic, some_basics_tests)
{
    cr_assert_eq(42, 42);
}