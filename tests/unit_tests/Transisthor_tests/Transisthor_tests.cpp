/*
** EPITECH PROJECT, 2022
** Project
** File description:
** Transisthor_tests
*/

#include <criterion/criterion.h>
#include "Transisthor/Transisthor.hpp"
#include "Error/Error.hpp"

using namespace transisthor_lib;
using namespace error_lib;

Test(transisthor_testing, basic_init)
{
    Transisthor transisthor = Transisthor();

    cr_assert_eq(42, 42);
}