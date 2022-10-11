/*
** EPITECH PROJECT, 2022
** R-Type
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
#include "CreateAlliedProjectile.hpp"
#include "CreateEnemy.hpp"
#include "CreateEnemyProjectile.hpp"

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
    Client temporaryClient = Client();
    communicator.addClientToList(temporaryClient);
    void *temp = transisthor.transitEcsDataToNetworkData<Position>(1, 6, pos, {1});
    void *networkAnswer = transisthor.transitNetworkDataToEcsDataComponent({Client(), temp, sizeof(Position), 30});

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
    Client temporaryClient = Client();
    communicator.addClientToList(temporaryClient);
    void *temp = transisthor.transitEcsDataToNetworkData<Destination>(1, 1, pos, {1});
    void *networkAnswer = transisthor.transitNetworkDataToEcsDataComponent({Client(), temp, sizeof(Destination), 30});

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
    Client temporaryClient = Client();
    communicator.addClientToList(temporaryClient);
    void *temp = transisthor.transitEcsDataToNetworkData<Equipment>(1, 2, pos, {1});
    void *networkAnswer = transisthor.transitNetworkDataToEcsDataComponent({Client(), temp, sizeof(Equipment), 30});

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
    Client temporaryClient = Client();
    communicator.addClientToList(temporaryClient);
    void *temp = transisthor.transitEcsDataToNetworkData<Invinsible>(1, 3, pos, {1});
    void *networkAnswer = transisthor.transitNetworkDataToEcsDataComponent({Client(), temp, sizeof(Invinsible), 30});

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
    Client temporaryClient = Client();
    communicator.addClientToList(temporaryClient);
    void *temp = transisthor.transitEcsDataToNetworkData<Invisible>(1, 4, pos, {1});
    void *networkAnswer = transisthor.transitNetworkDataToEcsDataComponent({Client(), temp, sizeof(Invisible), 30});

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
    Client temporaryClient = Client();
    communicator.addClientToList(temporaryClient);
    void *temp = transisthor.transitEcsDataToNetworkData<Life>(1, 5, pos, {1});
    void *networkAnswer = transisthor.transitNetworkDataToEcsDataComponent({Client(), temp, sizeof(Life), 30});

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
    Client temporaryClient = Client();
    communicator.addClientToList(temporaryClient);
    void *temp = transisthor.transitEcsDataToNetworkData<Velocity>(1, 7, pos, {1});
    void *networkAnswer = transisthor.transitNetworkDataToEcsDataComponent({Client(), temp, sizeof(Velocity), 30});

    cr_assert_eq(pos.multiplierOrdinate, 12);
    cr_assert_eq(pos.multiplierAbscissa, 10);
    newPos = buildComponentFromByteCode<Velocity>(networkAnswer);
    cr_assert_eq(newPos.multiplierOrdinate, 12);
    cr_assert_eq(newPos.multiplierAbscissa, 10);
}

Test(transisthor_testing, transit_to_a_non_valid_client)
{
    Communicator communicator = Communicator();
    World world = World(2);
    Transisthor transisthor = Transisthor(communicator, world);
    Velocity pos = Velocity(10, 12);
    try {
        void *temp = transisthor.transitEcsDataToNetworkData<Velocity>(1, 7, pos, {1});
        (void)temp;
        cr_assert_eq(41, 42);
    } catch (NetworkError &err) {
        cr_assert_eq(42, 42);
    }
}

Test(transisthor_testing, transit_get_a_server_id)
{
    Communicator communicator = Communicator();
    World world = World(2);
    Transisthor transisthor = Transisthor(communicator, world);
    Velocity pos = Velocity(10, 12);
    Client temporaryClient = Client();
    communicator.addClientToList(temporaryClient);
    try {
        void *temp = transisthor.transitEcsDataToNetworkData<Velocity>(1, 7, pos, {transisthor.getServerEndpointId()});
        (void)temp;
        cr_assert_eq(42, 42);
    } catch (NetworkError &err) {
        cr_assert_eq(41, 42);
    }
}

Test(transisthor_testing, transit_get_a_server_id_when_no_server_here)
{
    Communicator communicator = Communicator();
    World world = World(2);
    Transisthor transisthor = Transisthor(communicator, world);
    Velocity pos = Velocity(10, 12);
    try {
        void *temp = transisthor.transitEcsDataToNetworkData<Velocity>(1, 7, pos, {transisthor.getServerEndpointId()});
        (void)temp;
        cr_assert_eq(41, 42);
    } catch (NetworkError &err) {
        cr_assert_eq(42, 42);
    }
}

Test(transisthor_testing, transit_get_a_server_id_when_multiple_server_here)
{
    Communicator communicator = Communicator();
    World world = World(2);
    Transisthor transisthor = Transisthor(communicator, world);
    Velocity pos = Velocity(10, 12);
    Client temporaryClient = Client();
    Client temporaryClientTwo = Client("AAA", 10);
    communicator.addClientToList(temporaryClient);
    communicator.addClientToList(temporaryClientTwo);
    try {
        void *temp = transisthor.transitEcsDataToNetworkData<Velocity>(1, 7, pos, {transisthor.getServerEndpointId()});
        (void)temp;
        cr_assert_eq(41, 42);
    } catch (NetworkError &err) {
        cr_assert_eq(42, 42);
    }
}

Test(transisthor_testing, transit_enemy_entity)
{
    Communicator communicator = Communicator();
    World world = World(2);
    Transisthor transisthor = Transisthor(communicator, world);
    Velocity pos = Velocity(10, 12);
    Velocity newPos;
    Client temporaryClient = Client();
    communicator.addClientToList(temporaryClient);

    std::size_t entityId = createNewEnemy(world, 1, 2, 0, 0, 0, 1, 1, 1, 1, 1);

    Position entityPosition = world.getEntity(entityId).getComponent<Position>();

    void *temp = transisthor.transitEcsDataToNetworkDataEntityEnemy(entityId, entityPosition.x, entityPosition.y, {1});
    void *networkAnswer = transisthor.transitNetworkDataToEcsDataEntity({Client(), temp, 1, 31});

    int posX = 0;
    int posY = 0;

    std::memcpy(&posX, networkAnswer, sizeof(int));
    std::memcpy(&posY, (void *)((char *)networkAnswer + sizeof(int)), sizeof(int));
    cr_assert_eq(posX, 1);
    cr_assert_eq(posY, 2);
}

Test(transisthor_testing, transit_alliedProjectile_entity)
{
    Communicator communicator = Communicator();
    World world = World(2);
    Transisthor transisthor = Transisthor(communicator, world);
    Velocity pos = Velocity(10, 12);
    Velocity newPos;
    Client temporaryClient = Client();
    communicator.addClientToList(temporaryClient);

    std::size_t allied = world.addEntity()
                            .addComponent<Position>(1, 2)
                            .addComponent<Damage>(10)
                            .addComponent<Velocity>(1, 1)
                            .getId();

    std::size_t entityId = createNewAlliedProjectile(world, world.getEntity(allied));

    Position entityPosition = world.getEntity(entityId).getComponent<Position>();

    void *temp = transisthor.transitEcsDataToNetworkDataEntityAlliedProjectile(entityId, entityPosition.x, entityPosition.y, {1});
    void *networkAnswer = transisthor.transitNetworkDataToEcsDataEntity({Client(), temp, 1, 31});

    int posX = 0;
    int posY = 0;

    std::memcpy(&posX, networkAnswer, sizeof(int));
    std::memcpy(&posY, (void *)((char *)networkAnswer + sizeof(int)), sizeof(int));
    cr_assert_eq(posX, 1);
    cr_assert_eq(posY, 2);
}

Test(transisthor_testing, transit_enemyProjectile_entity)
{
    Communicator communicator = Communicator();
    World world = World(2);
    Transisthor transisthor = Transisthor(communicator, world);
    Velocity pos = Velocity(10, 12);
    Velocity newPos;
    Client temporaryClient = Client();
    communicator.addClientToList(temporaryClient);

    std::size_t enemy = world.addEntity()
                            .addComponent<Position>(1, 2)
                            .addComponent<Damage>(10)
                            .addComponent<Velocity>(1, 1)
                            .getId();

    std::size_t entityId = createNewEnemyProjectile(world, world.getEntity(enemy));

    Position entityPosition = world.getEntity(entityId).getComponent<Position>();

    void *temp = transisthor.transitEcsDataToNetworkDataEntityEnemyProjectile(entityId, entityPosition.x, entityPosition.y, {1});
    void *networkAnswer = transisthor.transitNetworkDataToEcsDataEntity({Client(), temp, 1, 31});

    int posX = 0;
    int posY = 0;

    std::memcpy(&posX, networkAnswer, sizeof(int));
    std::memcpy(&posY, (void *)((char *)networkAnswer + sizeof(int)), sizeof(int));
    cr_assert_eq(posX, 1);
    cr_assert_eq(posY, 2);
}