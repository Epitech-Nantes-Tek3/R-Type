/*
** EPITECH PROJECT, 2022
** Project
** File description:
** entrypoint_tests
*/

#include <criterion/criterion.h>
#include "entrypoint.hpp"

Test(entry_point_testing, template)
{
    communicator_lib::entrypoint();
    cr_assert_eq(42, 42);
}