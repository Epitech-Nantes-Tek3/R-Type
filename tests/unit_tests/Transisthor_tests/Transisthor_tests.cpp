/*
** EPITECH PROJECT, 2022
** Project
** File description:
** Transisthor_tests
*/

#include <criterion/criterion.h>
#include "Error/Error.hpp"
#include "GameComponents/DestinationComponent.hpp"
#include "GameComponents/EquipmentComponent.hpp"
#include "GameComponents/InvinsibleComponent.hpp"
#include "GameComponents/InvisibleComponent.hpp"
#include "GameComponents/LifeComponent.hpp"
#include "GameComponents/PositionComponent.hpp"
#include "GameComponents/VelocityComponent.hpp"
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

Test(transisthor_testing, transit_position_component)
{
    Communicator communicator = Communicator();
    World world = World(2);
    Transisthor transisthor = Transisthor(communicator, world);
    Position pos = Position(10, 95);
    Position newPos;
    void *temp = transisthor.transitEcsDataToNetworkData<Position>(1, 6, pos);
    void *networkAnswer = transisthor.transitNetworkDataToEcsData({Client(), temp, sizeof(Position), 30});

    cr_assert_eq(pos.x, 10);
    cr_assert_eq(pos.y, 95);
    newPos = buildComponentFromByteCode<Position>(networkAnswer);
    cr_assert_eq(newPos.x, 10);
    cr_assert_eq(newPos.y, 95);
}

Test(transisthor_testing, transit_destination_component)
{
    Communicator communicator = Communicator();
    World world = World(2);
    Transisthor transisthor = Transisthor(communicator, world);
    Destination pos = Destination(10, 95);
    Destination newPos;
    void *temp = transisthor.transitEcsDataToNetworkData<Destination>(1, 1, pos);
    void *networkAnswer = transisthor.transitNetworkDataToEcsData({Client(), temp, sizeof(Destination), 30});

    cr_assert_eq(pos.x, 10);
    cr_assert_eq(pos.y, 95);
    newPos = buildComponentFromByteCode<Destination>(networkAnswer);
    cr_assert_eq(newPos.x, 10);
    cr_assert_eq(newPos.y, 95);
}

Test(transisthor_testing, transit_equipment_component)
{
    Communicator communicator = Communicator();
    World world = World(2);
    Transisthor transisthor = Transisthor(communicator, world);
    Equipment pos = Equipment(10);
    Equipment newPos;
    void *temp = transisthor.transitEcsDataToNetworkData<Equipment>(1, 2, pos);
    void *networkAnswer = transisthor.transitNetworkDataToEcsData({Client(), temp, sizeof(Equipment), 30});

    cr_assert_eq(pos.typeId, 10);
    newPos = buildComponentFromByteCode<Equipment>(networkAnswer);
    cr_assert_eq(newPos.typeId, 10);
}

Test(transisthor_testing, transit_invinsible_component)
{
    Communicator communicator = Communicator();
    World world = World(2);
    Transisthor transisthor = Transisthor(communicator, world);
    Invinsible pos = Invinsible();
    Invinsible newPos;
    void *temp = transisthor.transitEcsDataToNetworkData<Invinsible>(1, 3, pos);
    void *networkAnswer = transisthor.transitNetworkDataToEcsData({Client(), temp, sizeof(Invinsible), 30});

    newPos = buildComponentFromByteCode<Invinsible>(networkAnswer);
    cr_assert_eq(42, 42);
}

Test(transisthor_testing, transit_invisible_component)
{
    Communicator communicator = Communicator();
    World world = World(2);
    Transisthor transisthor = Transisthor(communicator, world);
    Invisible pos = Invisible();
    Invisible newPos;
    void *temp = transisthor.transitEcsDataToNetworkData<Invisible>(1, 4, pos);
    void *networkAnswer = transisthor.transitNetworkDataToEcsData({Client(), temp, sizeof(Invisible), 30});

    newPos = buildComponentFromByteCode<Invisible>(networkAnswer);
    cr_assert_eq(42, 42);
}

Test(transisthor_testing, transit_life_component)
{
    Communicator communicator = Communicator();
    World world = World(2);
    Transisthor transisthor = Transisthor(communicator, world);
    Life pos = Life(10);
    Life newPos;
    void *temp = transisthor.transitEcsDataToNetworkData<Life>(1, 5, pos);
    void *networkAnswer = transisthor.transitNetworkDataToEcsData({Client(), temp, sizeof(Life), 30});

    cr_assert_eq(pos.lifePoint, 10);
    newPos = buildComponentFromByteCode<Life>(networkAnswer);
    cr_assert_eq(newPos.lifePoint, 10);
}

Test(transisthor_testing, transit_velocity_component)
{
    Communicator communicator = Communicator();
    World world = World(2);
    Transisthor transisthor = Transisthor(communicator, world);
    Velocity pos = Velocity(10, 12);
    Velocity newPos;
    void *temp = transisthor.transitEcsDataToNetworkData<Velocity>(1, 7, pos);
    void *networkAnswer = transisthor.transitNetworkDataToEcsData({Client(), temp, sizeof(Velocity), 30});

    cr_assert_eq(pos.multiplierOrdinate, 12);
    cr_assert_eq(pos.multiplierAbscissa, 10);
    newPos = buildComponentFromByteCode<Velocity>(networkAnswer);
    cr_assert_eq(newPos.multiplierOrdinate, 12);
    cr_assert_eq(newPos.multiplierAbscissa, 10);
}
