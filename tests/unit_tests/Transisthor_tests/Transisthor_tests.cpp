/*
** EPITECH PROJECT, 2022
** Project
** File description:
** Transisthor_tests
*/

#include <criterion/criterion.h>
#include "Error/Error.hpp"
#include "Transisthor/Transisthor.hpp"

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

Test(transisthor_testing, transit_data_testing)
{
    Communicator communicator = Communicator();
    World world = World(2);
    Transisthor transisthor = Transisthor(communicator, world);
    Position pos = Position(10, 95);
    Position newPos;
    void *temp = transisthor.transitEcsDataToNetworkData<Position>(1, 3, pos);
    void *networkAnswer = transisthor.transitNetworkDataToEcsData({Client(), temp, sizeof(Position), 30});

    cr_assert_eq(pos.x, 10);
    cr_assert_eq(pos.y, 95);
    newPos = buildComponentFromByteCode<Position>(networkAnswer);
    cr_assert_eq(newPos.x, 10);
    cr_assert_eq(newPos.y, 95);
}