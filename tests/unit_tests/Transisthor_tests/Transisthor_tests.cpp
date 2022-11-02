/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** Transisthor_tests
*/

#include <criterion/criterion.h>
#include "Error/Error.hpp"
#include "Transisthor/Transisthor.hpp"
#include "Transisthor/TransisthorECSLogic/Client/Systems/SendNewlyCreatedToServer.hpp"
#include "Transisthor/TransisthorECSLogic/Server/Resources/NetworkableIdGenerator.hpp"
#include "Transisthor/TransisthorECSLogic/Server/Systems/SendNewlyCreatedToClients.hpp"
#include "R-TypeLogic/EntityManipulation/CreateEntitiesFunctions/CreateAlliedProjectile.hpp"
#include "R-TypeLogic/EntityManipulation/CreateEntitiesFunctions/CreateEnemy.hpp"
#include "R-TypeLogic/EntityManipulation/CreateEntitiesFunctions/CreateEnemyProjectile.hpp"
#include "R-TypeLogic/EntityManipulation/CreateEntitiesFunctions/CreateObstacle.hpp"
#include "R-TypeLogic/EntityManipulation/CreateEntitiesFunctions/CreatePlayer.hpp"
#include "R-TypeLogic/EntityManipulation/CreateEntitiesFunctions/CreateProjectile.hpp"
#include "R-TypeLogic/Global/Components/DeathComponent.hpp"
#include "R-TypeLogic/Global/Components/DestinationComponent.hpp"
#include "R-TypeLogic/Global/Components/EquipmentComponent.hpp"
#include "R-TypeLogic/Global/Components/InvinsibleComponent.hpp"
#include "R-TypeLogic/Global/Components/InvisibleComponent.hpp"
#include "R-TypeLogic/Global/Components/LifeComponent.hpp"
#include "R-TypeLogic/Global/Components/PositionComponent.hpp"
#include "R-TypeLogic/Global/Components/VelocityComponent.hpp"
#include "R-TypeLogic/Global/SharedResources/Random.hpp"

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
    void *temp = transisthor.transitEcsDataToNetworkData<Position>(1, 6, pos, {0});
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
    void *temp = transisthor.transitEcsDataToNetworkData<Destination>(1, 1, pos, {0});
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
    void *temp = transisthor.transitEcsDataToNetworkData<Equipment>(1, 2, pos, {0});
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
    void *temp = transisthor.transitEcsDataToNetworkData<Invinsible>(1, 3, pos, {0});
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
    void *temp = transisthor.transitEcsDataToNetworkData<Invisible>(1, 4, pos, {0});
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
    void *temp = transisthor.transitEcsDataToNetworkData<Life>(1, 5, pos, {0});
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
    void *temp = transisthor.transitEcsDataToNetworkData<Velocity>(1, 7, pos, {0});
    void *networkAnswer = transisthor.transitNetworkDataToEcsDataComponent({Client(), temp, sizeof(Velocity), 30});

    cr_assert_eq(pos.multiplierOrdinate, 12);
    cr_assert_eq(pos.multiplierAbscissa, 10);
    newPos = buildComponentFromByteCode<Velocity>(networkAnswer);
    cr_assert_eq(newPos.multiplierOrdinate, 12);
    cr_assert_eq(newPos.multiplierAbscissa, 10);
}

Test(transisthor_testing, transit_death_component)
{
    Communicator communicator = Communicator();
    World world = World(2);
    Transisthor transisthor = Transisthor(communicator, world);
    Death death = Death();
    Death newDeath;
    Client temporaryClient = Client();
    communicator.addClientToList(temporaryClient);
    void *temp = transisthor.transitEcsDataToNetworkData<Death>(1, 8, death, {0});
    void *networkAnswer = transisthor.transitNetworkDataToEcsDataComponent({Client(), temp, sizeof(Death), 30});

    cr_assert_eq(death.modified, true);
    newDeath = buildComponentFromByteCode<Death>(networkAnswer);
    cr_assert_eq(newDeath.modified, true);
}

Test(transisthor_testing, transit_to_a_non_valid_client)
{
    Communicator communicator = Communicator();
    World world = World(2);
    Transisthor transisthor = Transisthor(communicator, world);
    Velocity pos = Velocity(10, 12);
    try {
        void *temp = transisthor.transitEcsDataToNetworkData<Velocity>(1, 7, pos, {0});
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

    std::size_t entityId = createNewEnemy(world, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, Enemy::FIRE, "UUID");

    Position entityPosition = world.getEntity(entityId).getComponent<Position>();

    void *temp = transisthor.transitEcsDataToNetworkDataEntityEnemy(
        entityId, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, Enemy::FIRE, std::string("UUID"), {0});
    void *networkAnswer = transisthor.transitNetworkDataToEcsDataEntity({Client(), temp, 1, 31});

    int posX = 0;
    int posY = 0;
    double multiplierAbscissa = 0;
    double multiplierOrdinate = 0;
    short weight = 0;
    int sizeX = 0;
    int sizeY = 0;
    short life = 0;
    unsigned short damage = 0;
    unsigned short damageRadius = 0;
    unsigned short type;

    char *uuid =
        (char *)networkAnswer + sizeof(int) * 4 + sizeof(double) * 2 + sizeof(short) * 2 + sizeof(unsigned short) * 3;

    std::memcpy(&posX, networkAnswer, sizeof(int));
    std::memcpy(&posY, (void *)((char *)networkAnswer + sizeof(int)), sizeof(int));
    std::memcpy(&multiplierAbscissa, (void *)((char *)networkAnswer + sizeof(int) * 2), sizeof(double));
    std::memcpy(
        &multiplierOrdinate, (void *)((char *)networkAnswer + sizeof(int) * 2 + sizeof(double)), sizeof(double));
    std::memcpy(&weight, (void *)((char *)networkAnswer + sizeof(int) * 2 + sizeof(double) * 2), sizeof(short));
    std::memcpy(
        &sizeX, (void *)((char *)networkAnswer + sizeof(int) * 2 + sizeof(double) * 2 + sizeof(short)), sizeof(int));
    std::memcpy(
        &sizeY, (void *)((char *)networkAnswer + sizeof(int) * 3 + sizeof(double) * 2 + sizeof(short)), sizeof(int));
    std::memcpy(
        &life, (void *)((char *)networkAnswer + sizeof(int) * 4 + sizeof(double) * 2 + sizeof(short)), sizeof(short));
    std::memcpy(&damage, (void *)((char *)networkAnswer + sizeof(int) * 4 + sizeof(double) * 2 + sizeof(short) * 2),
        sizeof(unsigned short));
    std::memcpy(&damageRadius,
        (void *)((char *)networkAnswer + sizeof(int) * 4 + sizeof(double) * 2 + sizeof(short) * 2
            + sizeof(unsigned short)),
        sizeof(unsigned short));
    std::memcpy(&type,
        (void *)((char *)networkAnswer + sizeof(int) * 4 + sizeof(double) * 2 + sizeof(short) * 2
            + 2 * sizeof(unsigned short)),
        sizeof(unsigned short));

    cr_assert_eq(posX, 1);
    cr_assert_eq(posY, 2);
    cr_assert_eq(multiplierAbscissa, 3);
    cr_assert_eq(multiplierOrdinate, 4);
    cr_assert_eq(weight, 5);
    cr_assert_eq(sizeX, 6);
    cr_assert_eq(sizeY, 7);
    cr_assert_eq(life, 8);
    cr_assert_eq(damage, 9);
    cr_assert_eq(damageRadius, 10);
    cr_assert_eq(type, Enemy::FIRE);
    cr_assert_str_eq("UUID", uuid);
}

Test(transisthor_testing, transit_enemy_entity_without_uuid)
{
    Communicator communicator = Communicator();
    World world = World(2);
    Transisthor transisthor = Transisthor(communicator, world);
    Velocity pos = Velocity(10, 12);
    Velocity newPos;
    Client temporaryClient = Client();
    communicator.addClientToList(temporaryClient);

    world.addResource<RandomDevice>();

    std::size_t entityId = createNewEnemy(world, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, Enemy::ICE, "", 1);

    Position entityPosition = world.getEntity(entityId).getComponent<Position>();

    void *temp = transisthor.transitEcsDataToNetworkDataEntityEnemy(
        entityId, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, Enemy::ICE, std::string(""), {0});
    void *networkAnswer = transisthor.transitNetworkDataToEcsDataEntity({Client(), temp, 1, 31});

    int posX = 0;
    int posY = 0;
    double multiplierAbscissa = 0;
    double multiplierOrdinate = 0;
    short weight = 0;
    int sizeX = 0;
    int sizeY = 0;
    short life = 0;
    unsigned short damage = 0;
    unsigned short damageRadius = 0;
    unsigned short type = 0;

    char *uuid =
        (char *)networkAnswer + sizeof(int) * 4 + sizeof(double) * 2 + sizeof(short) * 2 + sizeof(unsigned short) * 3;

    std::memcpy(&posX, networkAnswer, sizeof(int));
    std::memcpy(&posY, (void *)((char *)networkAnswer + sizeof(int)), sizeof(int));
    std::memcpy(&multiplierAbscissa, (void *)((char *)networkAnswer + sizeof(int) * 2), sizeof(double));
    std::memcpy(
        &multiplierOrdinate, (void *)((char *)networkAnswer + sizeof(int) * 2 + sizeof(double)), sizeof(double));
    std::memcpy(&weight, (void *)((char *)networkAnswer + sizeof(int) * 2 + sizeof(double) * 2), sizeof(short));
    std::memcpy(
        &sizeX, (void *)((char *)networkAnswer + sizeof(int) * 2 + sizeof(double) * 2 + sizeof(short)), sizeof(int));
    std::memcpy(
        &sizeY, (void *)((char *)networkAnswer + sizeof(int) * 3 + sizeof(double) * 2 + sizeof(short)), sizeof(int));
    std::memcpy(
        &life, (void *)((char *)networkAnswer + sizeof(int) * 4 + sizeof(double) * 2 + sizeof(short)), sizeof(short));
    std::memcpy(&damage, (void *)((char *)networkAnswer + sizeof(int) * 4 + sizeof(double) * 2 + sizeof(short) * 2),
        sizeof(unsigned short));
    std::memcpy(&damageRadius,
        (void *)((char *)networkAnswer + sizeof(int) * 4 + sizeof(double) * 2 + sizeof(short) * 2
            + sizeof(unsigned short)),
        sizeof(unsigned short));
    std::memcpy(&type,
        (void *)((char *)networkAnswer + sizeof(int) * 4 + sizeof(double) * 2 + sizeof(short) * 2
            + 2 * sizeof(unsigned short)),
        sizeof(unsigned short));

    cr_assert_eq(posX, 1);
    cr_assert_eq(posY, 2);
    cr_assert_eq(multiplierAbscissa, 3);
    cr_assert_eq(multiplierOrdinate, 4);
    cr_assert_eq(weight, 5);
    cr_assert_eq(sizeX, 6);
    cr_assert_eq(sizeY, 7);
    cr_assert_eq(life, 8);
    cr_assert_eq(damage, 9);
    cr_assert_eq(damageRadius, 10);
    cr_assert_eq(type, Enemy::ICE);
    cr_assert_str_eq("", uuid);
}

Test(transisthor_testing, transit_player_entity)
{
    Communicator communicator = Communicator();
    World world = World(2);
    Transisthor transisthor = Transisthor(communicator, world);
    Velocity pos = Velocity(10, 12);
    Velocity newPos;
    Client temporaryClient = Client();
    communicator.addClientToList(temporaryClient);

    std::size_t entityId = createNewPlayer(world, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, false, 2, "Lucas", "UUID");

    std::string plyName = world.getEntity(entityId).getComponent<Player>().name;

    void *temp = transisthor.transitEcsDataToNetworkDataEntityPlayer(
        entityId, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, false, 2, plyName, std::string("UUID"), {0});
    void *networkAnswer = transisthor.transitNetworkDataToEcsDataEntity({Client(), temp, 1, 31});

    int posX = 0;
    int posY = 0;
    double multiplierAbscissa = 0;
    double multiplierOrdinate = 0;
    short weight = 0;
    int sizeX = 0;
    int sizeY = 0;
    short life = 0;
    unsigned short damage = 0;
    unsigned short damageRadius = 0;
    bool isControlable = true;
    unsigned short playerIdentifier = 0;

    char *playerName = (char *)networkAnswer + sizeof(int) * 4 + sizeof(double) * 2 + sizeof(short) * 2
        + sizeof(unsigned short) * 3 + sizeof(bool);
    char *uuid = (char *)networkAnswer + sizeof(int) * 4 + sizeof(double) * 2 + sizeof(short) * 2
        + sizeof(unsigned short) * 3 + sizeof(bool) + sizeof(char) * 5;

    std::memcpy(&posX, networkAnswer, sizeof(int));
    std::memcpy(&posY, (void *)((char *)networkAnswer + sizeof(int)), sizeof(int));
    std::memcpy(&multiplierAbscissa, (void *)((char *)networkAnswer + sizeof(int) * 2), sizeof(double));
    std::memcpy(
        &multiplierOrdinate, (void *)((char *)networkAnswer + sizeof(int) * 2 + sizeof(double)), sizeof(double));
    std::memcpy(&weight, (void *)((char *)networkAnswer + sizeof(int) * 2 + sizeof(double) * 2), sizeof(short));
    std::memcpy(
        &sizeX, (void *)((char *)networkAnswer + sizeof(int) * 2 + sizeof(double) * 2 + sizeof(short)), sizeof(int));
    std::memcpy(
        &sizeY, (void *)((char *)networkAnswer + sizeof(int) * 3 + sizeof(double) * 2 + sizeof(short)), sizeof(int));
    std::memcpy(
        &life, (void *)((char *)networkAnswer + sizeof(int) * 4 + sizeof(double) * 2 + sizeof(short)), sizeof(short));
    std::memcpy(&damage, (void *)((char *)networkAnswer + sizeof(int) * 4 + sizeof(double) * 2 + sizeof(short) * 2),
        sizeof(unsigned short));
    std::memcpy(&damageRadius,
        (void *)((char *)networkAnswer + sizeof(int) * 4 + sizeof(double) * 2 + sizeof(short) * 2
            + sizeof(unsigned short)),
        sizeof(unsigned short));
    std::memcpy(&isControlable,
        (void *)((char *)networkAnswer + sizeof(int) * 4 + sizeof(double) * 2 + sizeof(short) * 2
            + sizeof(unsigned short) * 2),
        sizeof(bool));
    std::memcpy(&playerIdentifier,
        (void *)((char *)networkAnswer + sizeof(int) * 4 + sizeof(double) * 2 + sizeof(short) * 2
            + sizeof(unsigned short) * 2 + sizeof(bool)),
        sizeof(unsigned short));

    std::string playerNameStr(6, '\0');

    for (int i = 0; i < 5; i++)
        playerNameStr[i] = playerName[i];

    std::string uuidStr(5, '\0');

    for (int i = 0; i < 4; i++)
        uuidStr[i] = uuid[i];

    cr_assert_eq(posX, 1);
    cr_assert_eq(posY, 2);
    cr_assert_eq(multiplierAbscissa, 3);
    cr_assert_eq(multiplierOrdinate, 4);
    cr_assert_eq(weight, 5);
    cr_assert_eq(sizeX, 6);
    cr_assert_eq(sizeY, 7);
    cr_assert_eq(life, 8);
    cr_assert_eq(damage, 9);
    cr_assert_eq(damageRadius, 10);
    cr_assert_eq(isControlable, false);
    cr_assert_eq(playerIdentifier, 2);
    cr_assert_str_eq(playerNameStr.c_str(), "Lucas");
    cr_assert_str_eq("UUID", uuidStr.c_str());
}

Test(transisthor_testing, transit_player_entity_without_uuid)
{
    Communicator communicator = Communicator();
    World world = World(2);
    Transisthor transisthor = Transisthor(communicator, world);
    Velocity pos = Velocity(10, 12);
    Velocity newPos;
    Client temporaryClient = Client();
    communicator.addClientToList(temporaryClient);

    std::size_t entityId = createNewPlayer(world, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, false, 2, "Lucas", "", 1);

    std::string plyName = world.getEntity(entityId).getComponent<Player>().name;

    void *temp = transisthor.transitEcsDataToNetworkDataEntityPlayer(
        entityId, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, false, 2, plyName, std::string(""), {0});
    void *networkAnswer = transisthor.transitNetworkDataToEcsDataEntity({Client(), temp, 1, 31});

    int posX = 0;
    int posY = 0;
    double multiplierAbscissa = 0;
    double multiplierOrdinate = 0;
    short weight = 0;
    int sizeX = 0;
    int sizeY = 0;
    short life = 0;
    unsigned short damage = 0;
    unsigned short damageRadius = 0;
    bool isControlable = true;
    unsigned short playerIdentifier = 0;

    char *playerName = (char *)networkAnswer + sizeof(int) * 4 + sizeof(double) * 2 + sizeof(short) * 2
        + sizeof(unsigned short) * 3 + sizeof(bool);
    char *uuid = (char *)networkAnswer + sizeof(int) * 4 + sizeof(double) * 2 + sizeof(short) * 2
        + sizeof(unsigned short) * 3 + sizeof(bool) + sizeof(char) * 5;

    std::memcpy(&posX, networkAnswer, sizeof(int));
    std::memcpy(&posY, (void *)((char *)networkAnswer + sizeof(int)), sizeof(int));
    std::memcpy(&multiplierAbscissa, (void *)((char *)networkAnswer + sizeof(int) * 2), sizeof(double));
    std::memcpy(
        &multiplierOrdinate, (void *)((char *)networkAnswer + sizeof(int) * 2 + sizeof(double)), sizeof(double));
    std::memcpy(&weight, (void *)((char *)networkAnswer + sizeof(int) * 2 + sizeof(double) * 2), sizeof(short));
    std::memcpy(
        &sizeX, (void *)((char *)networkAnswer + sizeof(int) * 2 + sizeof(double) * 2 + sizeof(short)), sizeof(int));
    std::memcpy(
        &sizeY, (void *)((char *)networkAnswer + sizeof(int) * 3 + sizeof(double) * 2 + sizeof(short)), sizeof(int));
    std::memcpy(
        &life, (void *)((char *)networkAnswer + sizeof(int) * 4 + sizeof(double) * 2 + sizeof(short)), sizeof(short));
    std::memcpy(&damage, (void *)((char *)networkAnswer + sizeof(int) * 4 + sizeof(double) * 2 + sizeof(short) * 2),
        sizeof(unsigned short));
    std::memcpy(&damageRadius,
        (void *)((char *)networkAnswer + sizeof(int) * 4 + sizeof(double) * 2 + sizeof(short) * 2
            + sizeof(unsigned short)),
        sizeof(unsigned short));
    std::memcpy(&isControlable,
        (void *)((char *)networkAnswer + sizeof(int) * 4 + sizeof(double) * 2 + sizeof(short) * 2
            + sizeof(unsigned short) * 2),
        sizeof(bool));
    std::memcpy(&playerIdentifier,
        (void *)((char *)networkAnswer + sizeof(int) * 4 + sizeof(double) * 2 + sizeof(short) * 2
            + sizeof(unsigned short) * 2 + sizeof(bool)),
        sizeof(unsigned short));

    std::string playerNameStr(6, '\0');

    for (int i = 0; i < 5; i++)
        playerNameStr[i] = playerName[i];

    cr_assert_eq(posX, 1);
    cr_assert_eq(posY, 2);
    cr_assert_eq(multiplierAbscissa, 3);
    cr_assert_eq(multiplierOrdinate, 4);
    cr_assert_eq(weight, 5);
    cr_assert_eq(sizeX, 6);
    cr_assert_eq(sizeY, 7);
    cr_assert_eq(life, 8);
    cr_assert_eq(damage, 9);
    cr_assert_eq(damageRadius, 10);
    cr_assert_eq(isControlable, false);
    cr_assert_eq(playerIdentifier, 2);
    cr_assert_str_eq(playerNameStr.c_str(), "Lucas");
    cr_assert_str_eq("", uuid);
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
                             .addComponent<Networkable>(10)
                             .addComponent<Position>(1, 2)
                             .addComponent<Damage>(10)
                             .addComponent<Velocity>(1, 1)
                             .getId();

    unsigned short entityId = createNewAlliedProjectile(world, world.getEntity(allied), "UUID", 1);

    void *temp = transisthor.transitEcsDataToNetworkDataEntityAlliedProjectile(entityId, 10, std::string("UUID"), {0});
    void *networkAnswer = transisthor.transitNetworkDataToEcsDataEntity({Client(), temp, 1, 31});

    unsigned short newAllied = 0;
    char *uuid = (char *)networkAnswer + sizeof(unsigned short);

    std::memcpy(&newAllied, networkAnswer, sizeof(unsigned short));
    cr_assert_eq(newAllied, 10);
    cr_assert_str_eq("UUID", uuid);
}

Test(transisthor_testing, transit_alliedProjectile_entity_empty_uuid)
{
    Communicator communicator = Communicator();
    World world = World(2);
    Transisthor transisthor = Transisthor(communicator, world);
    Velocity pos = Velocity(10, 12);
    Velocity newPos;
    Client temporaryClient = Client();
    communicator.addClientToList(temporaryClient);

    std::size_t allied = world.addEntity()
                             .addComponent<Networkable>(10)
                             .addComponent<Position>(1, 2)
                             .addComponent<Damage>(10)
                             .addComponent<Velocity>(1, 1)
                             .getId();

    unsigned short entityId = createNewAlliedProjectile(world, world.getEntity(allied), "", 1);

    void *temp = transisthor.transitEcsDataToNetworkDataEntityAlliedProjectile(entityId, 10, std::string(""), {0});
    (void)temp;
    cr_assert_eq(42, 42);
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

    world.addEntity()
        .addComponent<Networkable>(10)
        .addComponent<Position>(1, 2)
        .addComponent<Damage>(10)
        .addComponent<Velocity>(1, 1)
        .getId();

    std::vector<std::shared_ptr<ecs::Entity>> joined = world.joinEntities<Damage>();

    unsigned short entityId = createNewEnemyProjectile(world, joined.at(0), "UUID");
    void *temp = transisthor.transitEcsDataToNetworkDataEntityEnemyProjectile(entityId, 10, std::string("UUID"), {0});
    (void)temp;
    void *networkAnswer = transisthor.transitNetworkDataToEcsDataEntity({Client(), temp, 1, 31});

    unsigned short newEnemy = 0;

    char *uuid = (char *)networkAnswer + sizeof(unsigned short);

    std::memcpy(&newEnemy, networkAnswer, sizeof(unsigned short));
    cr_assert_eq(newEnemy, 10);
    cr_assert_str_eq("UUID", uuid);
}

Test(transisthor_testing, transit_enemyProjectile_entity_without_uuid)
{
    Communicator communicator = Communicator();
    World world = World(2);
    Transisthor transisthor = Transisthor(communicator, world);
    Velocity pos = Velocity(10, 12);
    Velocity newPos;
    Client temporaryClient = Client();
    communicator.addClientToList(temporaryClient);

    std::size_t enemy = world.addEntity()
                            .addComponent<Networkable>(10)
                            .addComponent<Position>(1, 2)
                            .addComponent<Damage>(10)
                            .addComponent<Velocity>(1, 1)
                            .getId();

    std::vector<std::shared_ptr<ecs::Entity>> joined = world.joinEntities<Damage>();

    unsigned short entityId = createNewEnemyProjectile(world, joined.at(0), "", 1);

    void *temp = transisthor.transitEcsDataToNetworkDataEntityEnemyProjectile(entityId, enemy, std::string(""), {0});
    (void)temp;
    cr_assert_eq(42, 42);
}

Test(transisthor_testing, transit_obstacle_entity)
{
    Communicator communicator = Communicator();
    World world = World(2);
    Transisthor transisthor = Transisthor(communicator, world);
    Velocity pos = Velocity(10, 12);
    Velocity newPos;
    Client temporaryClient = Client();
    communicator.addClientToList(temporaryClient);

    std::size_t entityId = createNewObstacle(world, 10, 120, 5, "UUID");

    Position entityPosition = world.getEntity(entityId).getComponent<Position>();

    void *temp = transisthor.transitEcsDataToNetworkDataEntityObstacle(
        entityId, entityPosition.x, entityPosition.y, 5, std::string("UUID"), {0});
    void *networkAnswer = transisthor.transitNetworkDataToEcsDataEntity({Client(), temp, 1, 31});

    int posX = 0;
    int posY = 0;
    unsigned short damage = 0;

    char *uuid = (char *)networkAnswer + sizeof(int) * 2 + sizeof(unsigned short);

    std::memcpy(&posX, networkAnswer, sizeof(int));
    std::memcpy(&posY, (void *)((char *)networkAnswer + sizeof(int)), sizeof(int));
    std::memcpy(&damage, (void *)((char *)networkAnswer + sizeof(int) * 2), sizeof(unsigned short));
    cr_assert_eq(posX, 10);
    cr_assert_eq(posY, 120);
    cr_assert_eq(damage, 5);
    cr_assert_str_eq("UUID", uuid);
}

Test(transisthor_testing, transit_obstacle_entity_without_uuid)
{
    Communicator communicator = Communicator();
    World world = World(2);
    Transisthor transisthor = Transisthor(communicator, world);
    Velocity pos = Velocity(10, 12);
    Velocity newPos;
    Client temporaryClient = Client();
    communicator.addClientToList(temporaryClient);

    std::size_t entityId = createNewObstacle(world, 10, 120, 5, "", 1);

    Position entityPosition = world.getEntity(entityId).getComponent<Position>();

    void *temp = transisthor.transitEcsDataToNetworkDataEntityObstacle(
        entityId, entityPosition.x, entityPosition.y, 5, std::string(""), {0});
    void *networkAnswer = transisthor.transitNetworkDataToEcsDataEntity({Client(), temp, 1, 31});

    int posX = 0;
    int posY = 0;
    unsigned short damage = 0;

    char *uuid = (char *)networkAnswer + sizeof(int) * 2 + sizeof(unsigned short);

    std::memcpy(&posX, networkAnswer, sizeof(int));
    std::memcpy(&posY, (void *)((char *)networkAnswer + sizeof(int)), sizeof(int));
    std::memcpy(&damage, (void *)((char *)networkAnswer + sizeof(int) * 2), sizeof(unsigned short));
    cr_assert_eq(posX, 10);
    cr_assert_eq(posY, 120);
    cr_assert_eq(damage, 5);
    cr_assert_str_eq("", uuid);
}

Test(transisthor_testing, transit_projectile_entity)
{
    Communicator communicator = Communicator();
    World world = World(2);
    Transisthor transisthor = Transisthor(communicator, world);
    Velocity pos = Velocity(10, 12);
    Velocity newPos;
    Client temporaryClient = Client();
    communicator.addClientToList(temporaryClient);

    std::size_t entityId = createNewProjectile(world, 10, 120, 4, 5, 1, "UUID");

    Position entityPosition = world.getEntity(entityId).getComponent<Position>();
    Velocity entityVel = world.getEntity(entityId).getComponent<Velocity>();

    void *temp = transisthor.transitEcsDataToNetworkDataEntityProjectile(entityId, entityPosition.x, entityPosition.y,
        entityVel.multiplierAbscissa, entityVel.multiplierOrdinate, 1, std::string("UUID"), {0});
    void *networkAnswer = transisthor.transitNetworkDataToEcsDataEntity({Client(), temp, 1, 31});

    int posX = 0;
    int posY = 0;
    double velAbsc = 0;
    double velOrd = 0;
    unsigned short damage = 0;

    char *uuid = (char *)networkAnswer + sizeof(int) * 2 + sizeof(double) * 2 + sizeof(unsigned short);

    std::memcpy(&posX, networkAnswer, sizeof(int));
    std::memcpy(&posY, (void *)((char *)networkAnswer + sizeof(int)), sizeof(int));
    std::memcpy(&velAbsc, (void *)((char *)networkAnswer + sizeof(int) * 2), sizeof(double));
    std::memcpy(&velOrd, (void *)((char *)networkAnswer + sizeof(int) * 2 + sizeof(double)), sizeof(double));
    std::memcpy(
        &damage, (void *)((char *)networkAnswer + sizeof(int) * 2 + sizeof(double) * 2), sizeof(unsigned short));
    cr_assert_eq(posX, 10);
    cr_assert_eq(posY, 120);
    cr_assert_eq(velAbsc, 4);
    cr_assert_eq(velOrd, 5);
    cr_assert_eq(damage, 1);
    cr_assert_str_eq("UUID", uuid);
}

Test(transisthor_testing, transit_projectile_entity_without_uuid)
{
    Communicator communicator = Communicator();
    World world = World(2);
    Transisthor transisthor = Transisthor(communicator, world);
    Velocity pos = Velocity(10, 12);
    Velocity newPos;
    Client temporaryClient = Client();
    communicator.addClientToList(temporaryClient);

    std::size_t entityId = createNewProjectile(world, 10, 120, 4, 5, 1, "", 1);

    Position entityPosition = world.getEntity(entityId).getComponent<Position>();
    Velocity entityVel = world.getEntity(entityId).getComponent<Velocity>();

    void *temp = transisthor.transitEcsDataToNetworkDataEntityProjectile(entityId, entityPosition.x, entityPosition.y,
        entityVel.multiplierAbscissa, entityVel.multiplierOrdinate, 1, std::string(""), {0});
    void *networkAnswer = transisthor.transitNetworkDataToEcsDataEntity({Client(), temp, 1, 31});

    int posX = 0;
    int posY = 0;
    double velAbsc = 0;
    double velOrd = 0;
    unsigned short damage = 0;

    char *uuid = (char *)networkAnswer + sizeof(int) * 2 + sizeof(double) * 2 + sizeof(unsigned short);

    std::memcpy(&posX, networkAnswer, sizeof(int));
    std::memcpy(&posY, (void *)((char *)networkAnswer + sizeof(int)), sizeof(int));
    std::memcpy(&velAbsc, (void *)((char *)networkAnswer + sizeof(int) * 2), sizeof(double));
    std::memcpy(&velOrd, (void *)((char *)networkAnswer + sizeof(int) * 2 + sizeof(double)), sizeof(double));
    std::memcpy(
        &damage, (void *)((char *)networkAnswer + sizeof(int) * 2 + sizeof(double) * 2), sizeof(unsigned short));
    cr_assert_eq(posX, 10);
    cr_assert_eq(posY, 120);
    cr_assert_eq(velAbsc, 4);
    cr_assert_eq(velOrd, 5);
    cr_assert_eq(damage, 1);
    cr_assert_str_eq("", uuid);
}

Test(transisthor_lib, test_networkable_id_generator_resource)
{
    World world = World(2);

    world.addResource<NetworkableIdGenerator>();

    cr_assert_eq(1, world.getResource<NetworkableIdGenerator>().generateNewNetworkableId());
    cr_assert_eq(2, world.getResource<NetworkableIdGenerator>().generateNewNetworkableId());
    cr_assert_eq(3, world.getResource<NetworkableIdGenerator>().generateNewNetworkableId());
}
