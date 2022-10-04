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
using namespace communicator_lib;
using namespace ecs;
using namespace error_lib;

Test(transisthor_testing, basic_init)
{
    Communicator communicator = Communicator();
    World world = World(2);
    Transisthor transisthor = Transisthor(communicator, world);

    cr_assert_eq(42, 42);
}