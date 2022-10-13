/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** Transisthor
*/

/// @file libs/Transisthor/Transisthor.cpp

#include "Transisthor.hpp"
#include "Error/Error.hpp"
#include "GameComponents/DestinationComponent.hpp"
#include "GameComponents/EquipmentComponent.hpp"
#include "GameComponents/InvinsibleComponent.hpp"
#include "GameComponents/InvisibleComponent.hpp"
#include "GameComponents/LifeComponent.hpp"
#include "GameComponents/PositionComponent.hpp"
#include "GameComponents/VelocityComponent.hpp"
#include "TransisthorECSLogic/Both/Components/Networkable.hpp"

using namespace transisthor_lib;
using namespace error_lib;
using namespace ecs;

Transisthor::Transisthor(Communicator &communicator, World &ecsWorld) : _communicator(communicator), _ecsWorld(ecsWorld)
{
    _componentConvertFunctionList[1] =
        std::bind(&Transisthor::componentConvertDestinationType, this, std::placeholders::_1, std::placeholders::_2);
    _componentConvertFunctionList[2] =
        std::bind(&Transisthor::componentConvertEquipmentType, this, std::placeholders::_1, std::placeholders::_2);
    _componentConvertFunctionList[3] =
        std::bind(&Transisthor::componentConvertInvinsibleType, this, std::placeholders::_1, std::placeholders::_2);
    _componentConvertFunctionList[4] =
        std::bind(&Transisthor::componentConvertInvisibleType, this, std::placeholders::_1, std::placeholders::_2);
    _componentConvertFunctionList[5] =
        std::bind(&Transisthor::componentConvertLifeType, this, std::placeholders::_1, std::placeholders::_2);
    _componentConvertFunctionList[6] =
        std::bind(&Transisthor::componentConvertPositionType, this, std::placeholders::_1, std::placeholders::_2);
    _componentConvertFunctionList[7] =
        std::bind(&Transisthor::componentConvertVelocityType, this, std::placeholders::_1, std::placeholders::_2);
    _entityConvertFunctionList[1] =
        std::bind(&Transisthor::entityConvertAlliedProjectileType, this, std::placeholders::_1, std::placeholders::_2);
    _entityConvertFunctionList[2] =
        std::bind(&Transisthor::entityConvertEnemyType, this, std::placeholders::_1, std::placeholders::_2);
    _entityConvertFunctionList[3] =
        std::bind(&Transisthor::entityConvertEnemyProjectileType, this, std::placeholders::_1, std::placeholders::_2);
    _entityConvertFunctionList[4] =
        std::bind(&Transisthor::entityConvertObstacleType, this, std::placeholders::_1, std::placeholders::_2);
    _entityConvertFunctionList[5] =
        std::bind(&Transisthor::entityConvertPlayerType, this, std::placeholders::_1, std::placeholders::_2);
    _entityConvertFunctionList[6] =
        std::bind(&Transisthor::entityConvertProjectileType, this, std::placeholders::_1, std::placeholders::_2);
}

void *Transisthor::transitNetworkDataToEcsDataComponent(Message networkData)
{
    unsigned short id = 0;
    unsigned short type = 0;
    void *object = nullptr;

    std::memcpy(&id, networkData.data, sizeof(unsigned short));
    std::memcpy(&type, (void *)((char *)networkData.data + sizeof(unsigned short)), sizeof(unsigned short));
    object = (void *)((char *)networkData.data + sizeof(unsigned short) * 2);
    if (_componentConvertFunctionList.find(type) == _componentConvertFunctionList.end())
        return object;                                                   /// THROW ERROR INVALID TYPE
    std::cerr << "A component have been transfered to ECS" << std::endl; /// ONLY USE FOR FUNCTIONAL TESTING
    _componentConvertFunctionList[type](id, object);
    return object;
}

void *Transisthor::transitNetworkDataToEcsDataEntity(Message networkData)
{
    unsigned short id = 0;
    unsigned short type = 0;
    void *object = nullptr;

    std::memcpy(&id, networkData.data, sizeof(unsigned short));
    std::memcpy(&type, (void *)((char *)networkData.data + sizeof(unsigned short)), sizeof(unsigned short));
    object = (void *)((char *)networkData.data + sizeof(unsigned short) * 2);
    if (_entityConvertFunctionList.find(type) == _entityConvertFunctionList.end())
        return object;                                                /// THROW ERROR INVALID TYPE
    std::cerr << "A entity have been transfered to ECS" << std::endl; /// ONLY USE FOR FUNCTIONAL TESTING
    _entityConvertFunctionList[type](id, object);
    return object;
}

void *Transisthor::transitEcsDataToNetworkDataEntityAlliedProjectile(
    unsigned short id, unsigned short allyId, std::string uuid, std::vector<unsigned short> destination)
{
    void *networkObject = std::malloc((sizeof(unsigned short) * 3 + sizeof(char) * uuid.size()));
    unsigned short typeId = 1;
    Client temporaryClient;

    if (networkObject == nullptr)
        throw error_lib::MallocError("Malloc failed.");
    std::memcpy(networkObject, &id, sizeof(unsigned short));
    std::memcpy((void *)((char *)networkObject + sizeof(unsigned short)), &typeId, sizeof(unsigned short));
    std::memcpy((void *)((char *)networkObject + sizeof(unsigned short) * 2), &allyId, sizeof(unsigned short));
    std::memcpy((void *)((char *)networkObject + sizeof(unsigned short) * 3), uuid.c_str(), sizeof(char) * uuid.size());
    for (auto it : destination) {
        temporaryClient = getClientByHisId(it);
        transisthor_lib::sendDataToAClientWithoutCommunicator(
            _communicator, temporaryClient, networkObject, (sizeof(unsigned short) * 3 + sizeof(char) * uuid.size()), 31);
    }
    return networkObject;
}

void *Transisthor::transitEcsDataToNetworkDataEntityEnemy(unsigned short id, int posX, int posY,
    double multiplierAbscissa, double multiplierOrdinate, short weight, int size_x, int size_y, short life,
    unsigned short damage, unsigned short damageRadius, std::string uuid, std::vector<unsigned short> destination)
{
    void *networkObject =
        std::malloc((sizeof(unsigned short) * 4 + sizeof(int) * 4 + sizeof(double) * 2 + sizeof(short) * 2 + sizeof(char) * uuid.size()));
    unsigned short typeId = 2;
    Client temporaryClient;

    if (networkObject == nullptr)
        throw error_lib::MallocError("Malloc failed.");
    std::memcpy(networkObject, &id, sizeof(unsigned short));
    std::memcpy((void *)((char *)networkObject + sizeof(unsigned short)), &typeId, sizeof(unsigned short));
    std::memcpy((void *)((char *)networkObject + sizeof(unsigned short) * 2), &posX, sizeof(int));
    std::memcpy((void *)((char *)networkObject + sizeof(unsigned short) * 2 + sizeof(int)), &posY, sizeof(int));
    std::memcpy((void *)((char *)networkObject + sizeof(unsigned short) * 2 + sizeof(int) * 2), &multiplierAbscissa,
        sizeof(double));
    std::memcpy((void *)((char *)networkObject + sizeof(unsigned short) * 2 + sizeof(int) * 2 + sizeof(double) * 1),
        &multiplierOrdinate, sizeof(double));
    std::memcpy((void *)((char *)networkObject + sizeof(unsigned short) * 2 + sizeof(int) * 2 + sizeof(double) * 2),
        &weight, sizeof(short));
    std::memcpy((void *)((char *)networkObject + sizeof(unsigned short) * 2 + sizeof(int) * 2 + sizeof(double) * 2
                    + sizeof(short)),
        &size_x, sizeof(int));
    std::memcpy((void *)((char *)networkObject + sizeof(unsigned short) * 2 + sizeof(int) * 3 + sizeof(double) * 2
                    + sizeof(short)),
        &size_y, sizeof(int));
    std::memcpy((void *)((char *)networkObject + sizeof(unsigned short) * 2 + sizeof(int) * 4 + sizeof(double) * 2
                    + sizeof(short)),
        &life, sizeof(short));
    std::memcpy((void *)((char *)networkObject + sizeof(unsigned short) * 2 + sizeof(int) * 4 + sizeof(double) * 2
                    + sizeof(short) * 2),
        &damage, sizeof(unsigned short));
    std::memcpy((void *)((char *)networkObject + sizeof(unsigned short) * 3 + sizeof(int) * 4 + sizeof(double) * 2
                    + sizeof(short) * 2),
        &damageRadius, sizeof(unsigned short));
    std::memcpy((void *)((char *)networkObject + sizeof(unsigned short) * 4 + sizeof(int) * 4 + sizeof(double) * 2
                    + sizeof(short) * 2),
        uuid.c_str(), sizeof(char) * uuid.size());
    for (auto it : destination) {
        temporaryClient = getClientByHisId(it);
        transisthor_lib::sendDataToAClientWithoutCommunicator(_communicator, temporaryClient, networkObject,
            (sizeof(unsigned short) * 4 + sizeof(int) * 4 + sizeof(double) * 2 + sizeof(short) * 2 + sizeof(char) * uuid.size()), 31);
    }
    return networkObject;
}

void *Transisthor::transitEcsDataToNetworkDataEntityEnemyProjectile(
    unsigned short id, unsigned short enemyId, std::string uuid, std::vector<unsigned short> destination)
{
    void *networkObject = std::malloc((sizeof(unsigned short) * 3 + sizeof(char) * uuid.size()));
    unsigned short typeId = 3;
    Client temporaryClient;

    if (networkObject == nullptr)
        throw error_lib::MallocError("Malloc failed.");
    std::memcpy(networkObject, &id, sizeof(unsigned short));
    std::memcpy((void *)((char *)networkObject + sizeof(unsigned short)), &typeId, sizeof(unsigned short));
    std::memcpy((void *)((char *)networkObject + sizeof(unsigned short) * 2), &enemyId, sizeof(unsigned short));
    std::memcpy((void *)((char *)networkObject + sizeof(unsigned short) * 3), uuid.c_str(), sizeof(char) * uuid.size());
    for (auto it : destination) {
        temporaryClient = getClientByHisId(it);
        transisthor_lib::sendDataToAClientWithoutCommunicator(
            _communicator, temporaryClient, networkObject, (sizeof(unsigned short) * 3 + sizeof(char) * uuid.size()), 31);
    }
    return networkObject;
}

void *Transisthor::transitEcsDataToNetworkDataEntityObstacle(
    unsigned short id, int posX, int posY, unsigned short damage, std::string uuid, std::vector<unsigned short> destination)
{
    void *networkObject = std::malloc((sizeof(unsigned short) * 3 + sizeof(int) * 2 + sizeof(char) * uuid.size()));
    unsigned short typeId = 4;
    Client temporaryClient;

    if (networkObject == nullptr)
        throw error_lib::MallocError("Malloc failed.");
    std::memcpy(networkObject, &id, sizeof(unsigned short));
    std::memcpy((void *)((char *)networkObject + sizeof(unsigned short)), &typeId, sizeof(unsigned short));
    std::memcpy((void *)((char *)networkObject + sizeof(unsigned short) * 2), &posX, sizeof(int));
    std::memcpy((void *)((char *)networkObject + sizeof(unsigned short) * 2 + sizeof(int)), &posY, sizeof(int));
    std::memcpy((void *)((char *)networkObject + sizeof(unsigned short) * 2 + sizeof(int) * 2), &damage,
        sizeof(unsigned short));
    std::memcpy((void *)((char *)networkObject + sizeof(unsigned short) * 3 + sizeof(int) * 2), uuid.c_str(),
        sizeof(char) * uuid.size());
    for (auto it : destination) {
        temporaryClient = getClientByHisId(it);
        transisthor_lib::sendDataToAClientWithoutCommunicator(
            _communicator, temporaryClient, networkObject, (sizeof(unsigned short) * 3 + sizeof(int) * 2 + sizeof(char) * uuid.size()), 31);
    }
    return networkObject;
}

void *Transisthor::transitEcsDataToNetworkDataEntityPlayer(unsigned short id, int posX, int posY,
    double multiplierAbscissa, double multiplierOrdinate, short weight, int size_x, int size_y, short life,
    unsigned short damage, unsigned short damageRadius, std::string uuid, std::vector<unsigned short> destination)
{
    void *networkObject =
        std::malloc((sizeof(unsigned short) * 4 + sizeof(int) * 4 + sizeof(double) * 2 + sizeof(short) * 2 + sizeof(char) * uuid.size()));
    unsigned short typeId = 5;
    Client temporaryClient;

    if (networkObject == nullptr)
        throw error_lib::MallocError("Malloc failed.");
    std::memcpy(networkObject, &id, sizeof(unsigned short));
    std::memcpy((void *)((char *)networkObject + sizeof(unsigned short)), &typeId, sizeof(unsigned short));
    std::memcpy((void *)((char *)networkObject + sizeof(unsigned short) * 2), &posX, sizeof(int));
    std::memcpy((void *)((char *)networkObject + sizeof(unsigned short) * 2 + sizeof(int)), &posY, sizeof(int));
    std::memcpy((void *)((char *)networkObject + sizeof(unsigned short) * 2 + sizeof(int) * 2), &multiplierAbscissa,
        sizeof(double));
    std::memcpy((void *)((char *)networkObject + sizeof(unsigned short) * 2 + sizeof(int) * 2 + sizeof(double) * 1),
        &multiplierOrdinate, sizeof(double));
    std::memcpy((void *)((char *)networkObject + sizeof(unsigned short) * 2 + sizeof(int) * 2 + sizeof(double) * 2),
        &weight, sizeof(short));
    std::memcpy((void *)((char *)networkObject + sizeof(unsigned short) * 2 + sizeof(int) * 2 + sizeof(double) * 2
                    + sizeof(short)),
        &size_x, sizeof(int));
    std::memcpy((void *)((char *)networkObject + sizeof(unsigned short) * 2 + sizeof(int) * 3 + sizeof(double) * 2
                    + sizeof(short)),
        &size_y, sizeof(int));
    std::memcpy((void *)((char *)networkObject + sizeof(unsigned short) * 2 + sizeof(int) * 4 + sizeof(double) * 2
                    + sizeof(short)),
        &life, sizeof(short));
    std::memcpy((void *)((char *)networkObject + sizeof(unsigned short) * 2 + sizeof(int) * 4 + sizeof(double) * 2
                    + sizeof(short) * 2),
        &damage, sizeof(unsigned short));
    std::memcpy((void *)((char *)networkObject + sizeof(unsigned short) * 3 + sizeof(int) * 4 + sizeof(double) * 2
                    + sizeof(short) * 2),
        &damageRadius, sizeof(unsigned short));
    std::memcpy((void *)((char *)networkObject + sizeof(unsigned short) * 4 + sizeof(int) * 4 + sizeof(double) * 2
                    + sizeof(short) * 2),
        uuid.c_str(), sizeof(char) * uuid.size());
    for (auto it : destination) {
        temporaryClient = getClientByHisId(it);
        transisthor_lib::sendDataToAClientWithoutCommunicator(_communicator, temporaryClient, networkObject,
            (sizeof(unsigned short) * 4 + sizeof(int) * 4 + sizeof(double) * 2 + sizeof(short) * 2 + sizeof(char) * uuid.size()), 31);
    }
    return networkObject;
}

void *Transisthor::transitEcsDataToNetworkDataEntityProjectile(unsigned short id, int posX, int posY, double velAbsc,
    double velOrd, unsigned short damage, std::string uuid, std::vector<unsigned short> destination)
{
    void *networkObject = std::malloc((sizeof(unsigned short) * 3 + sizeof(int) * 2 + sizeof(double) * 2 + sizeof(char) * uuid.size()));
    unsigned short typeId = 6;
    Client temporaryClient;

    if (networkObject == nullptr)
        throw error_lib::MallocError("Malloc failed.");
    std::memcpy(networkObject, &id, sizeof(unsigned short));
    std::memcpy((void *)((char *)networkObject + sizeof(unsigned short)), &typeId, sizeof(unsigned short));
    std::memcpy((void *)((char *)networkObject + sizeof(unsigned short) * 2), &posX, sizeof(int));
    std::memcpy((void *)((char *)networkObject + sizeof(unsigned short) * 2 + sizeof(int)), &posY, sizeof(int));
    std::memcpy(
        (void *)((char *)networkObject + sizeof(unsigned short) * 2 + sizeof(int) * 2), &velAbsc, sizeof(double));
    std::memcpy((void *)((char *)networkObject + sizeof(unsigned short) * 2 + sizeof(int) * 2 + sizeof(double)),
        &velOrd, sizeof(double));
    std::memcpy((void *)((char *)networkObject + sizeof(unsigned short) * 2 + sizeof(int) * 2 + sizeof(double) * 2),
        &damage, sizeof(unsigned short));
    std::memcpy((void *)((char *)networkObject + sizeof(unsigned short) * 3 + sizeof(int) * 2 + sizeof(double) * 2),
        uuid.c_str(), sizeof(char) * uuid.size());
    for (auto it : destination) {
        temporaryClient = getClientByHisId(it);
        transisthor_lib::sendDataToAClientWithoutCommunicator(_communicator, temporaryClient, networkObject,
            (sizeof(unsigned short) * 3 + sizeof(int) * 2 + sizeof(double) * 2 + sizeof(char) * uuid.size()), 31);
    }
    return networkObject;
}

Client Transisthor::getClientByHisId(unsigned short id) { return _communicator.getClientByHisId(id); }

unsigned short Transisthor::getServerEndpointId(void) { return _communicator.getServerEndpointId(); }

void Transisthor::componentConvertDestinationType(unsigned short id, void *byteCode)
{
    Destination newComponent = buildComponentFromByteCode<Destination>(byteCode);

    _ecsWorld.updateComponentOfAnEntityFromGivenDistinctiveComponent<Networkable, Destination>(
        Networkable(id), newComponent);
}

void Transisthor::componentConvertEquipmentType(unsigned short id, void *byteCode)
{
    Equipment newComponent = buildComponentFromByteCode<Equipment>(byteCode);

    _ecsWorld.updateComponentOfAnEntityFromGivenDistinctiveComponent<Networkable, Equipment>(
        Networkable(id), newComponent);
}

void Transisthor::componentConvertInvinsibleType(unsigned short id, void *byteCode)
{
    Invinsible newComponent = buildComponentFromByteCode<Invinsible>(byteCode);

    _ecsWorld.updateComponentOfAnEntityFromGivenDistinctiveComponent<Networkable, Invinsible>(
        Networkable(id), newComponent);
}

void Transisthor::componentConvertInvisibleType(unsigned short id, void *byteCode)
{
    Invisible newComponent = buildComponentFromByteCode<Invisible>(byteCode);

    _ecsWorld.updateComponentOfAnEntityFromGivenDistinctiveComponent<Networkable, Invisible>(
        Networkable(id), newComponent);
}

void Transisthor::componentConvertLifeType(unsigned short id, void *byteCode)
{
    Life newComponent = buildComponentFromByteCode<Life>(byteCode);

    _ecsWorld.updateComponentOfAnEntityFromGivenDistinctiveComponent<Networkable, Life>(Networkable(id), newComponent);
}

void Transisthor::componentConvertPositionType(unsigned short id, void *byteCode)
{
    Position newComponent = buildComponentFromByteCode<Position>(byteCode);

    _ecsWorld.updateComponentOfAnEntityFromGivenDistinctiveComponent<Networkable, Position>(
        Networkable(id), newComponent);
}

void Transisthor::componentConvertVelocityType(unsigned short id, void *byteCode)
{
    Velocity newComponent = buildComponentFromByteCode<Velocity>(byteCode);

    _ecsWorld.updateComponentOfAnEntityFromGivenDistinctiveComponent<Networkable, Velocity>(
        Networkable(id), newComponent);
}

void Transisthor::entityConvertAlliedProjectileType(unsigned short id, void *byteCode)
{
    unsigned short allyId = 0;
    char *uuid = (char *)byteCode + sizeof(unsigned short);

    std::memcpy(&allyId, byteCode, sizeof(unsigned short));
    (void)allyId;
    (void)uuid;
    (void)id;
    /// SEND THE NEW ENTITY TO ECS, WILL BE ADDED WHEN TRANSISTHOR WILL BE FULLY IMPLEMENTED
}

void Transisthor::entityConvertEnemyType(unsigned short id, void *byteCode)
{
    int posX = 0;
    int posY = 0;
    double multiplierAbscissa = 0;
    double multiplierOrdinate = 0;
    short weight = 0;
    int size_x = 0;
    int size_y = 0;
    short life = 0;
    unsigned short damage = 0;
    unsigned short damageRadius = 0;
    char *uuid = (char *)byteCode + sizeof(int) * 4 + sizeof(double) * 2 + sizeof(short) * 2 + sizeof(unsigned short) * 2;

    std::memcpy(&posX, byteCode, sizeof(int));
    std::memcpy(&posY, (void *)((char *)byteCode + sizeof(int)), sizeof(int));
    std::memcpy(&multiplierAbscissa, (void *)((char *)byteCode + sizeof(int) * 2), sizeof(double));
    std::memcpy(&multiplierOrdinate, (void *)((char *)byteCode + sizeof(int) * 2 + sizeof(double)), sizeof(double));
    std::memcpy(&weight, (void *)((char *)byteCode + sizeof(int) * 2 + sizeof(double) * 2), sizeof(short));
    std::memcpy(
        &size_x, (void *)((char *)byteCode + sizeof(int) * 2 + sizeof(double) * 2 + sizeof(short)), sizeof(int));
    std::memcpy(
        &size_y, (void *)((char *)byteCode + sizeof(int) * 3 + sizeof(double) * 2 + sizeof(short)), sizeof(int));
    std::memcpy(
        &life, (void *)((char *)byteCode + sizeof(int) * 4 + sizeof(double) * 2 + sizeof(short)), sizeof(short));
    std::memcpy(&damage, (void *)((char *)byteCode + sizeof(int) * 4 + sizeof(double) * 2 + sizeof(short) * 2),
        sizeof(unsigned short));
    std::memcpy(&damageRadius,
        (void *)((char *)byteCode + sizeof(int) * 4 + sizeof(double) * 2 + sizeof(short) * 2 + sizeof(unsigned short)),
        sizeof(unsigned short));
    (void)id;
    (void)posX;
    (void)posY;
    (void)multiplierAbscissa;
    (void)multiplierOrdinate;
    (void)weight;
    (void)size_x;
    (void)size_y;
    (void)life;
    (void)damage;
    (void)damageRadius;
    (void)uuid;
    /// SEND THE NEW ENTITY TO ECS, WILL BE ADDED WHEN TRANSISTHOR WILL BE FULLY IMPLEMENTED
}

void Transisthor::entityConvertEnemyProjectileType(unsigned short id, void *byteCode)
{
    unsigned short allyId = 0;
    char *uuid = (char *)byteCode + sizeof(unsigned short);

    std::memcpy(&allyId, byteCode, sizeof(unsigned short));
    (void)allyId;
    (void)uuid;
    (void)id;
    /// SEND THE NEW ENTITY TO ECS, WILL BE ADDED WHEN TRANSISTHOR WILL BE FULLY IMPLEMENTED
}

void Transisthor::entityConvertObstacleType(unsigned short id, void *byteCode)
{
    int posX = 0;
    int posY = 0;
    unsigned short damage = 0;
    char *uuid = (char *)byteCode + sizeof(int) * 2 + sizeof(unsigned short);

    std::memcpy(&posX, byteCode, sizeof(int));
    std::memcpy(&posY, (void *)((char *)byteCode + sizeof(int)), sizeof(int));
    std::memcpy(&damage, (void *)((char *)byteCode + sizeof(int) * 2), sizeof(unsigned short));
    (void)posX;
    (void)posY;
    (void)damage;
    (void)uuid;
    (void)id;
    /// SEND THE NEW ENTITY TO ECS, WILL BE ADDED WHEN TRANSISTHOR WILL BE FULLY IMPLEMENTED
}

void Transisthor::entityConvertPlayerType(unsigned short id, void *byteCode)
{
    int posX = 0;
    int posY = 0;
    double multiplierAbscissa = 0;
    double multiplierOrdinate = 0;
    short weight = 0;
    int size_x = 0;
    int size_y = 0;
    short life = 0;
    unsigned short damage = 0;
    unsigned short damageRadius = 0;
    char *uuid = (char *)byteCode + sizeof(int) * 4 + sizeof(double) * 2 + sizeof(short) * 2 + sizeof(unsigned short) * 2;

    std::memcpy(&posX, byteCode, sizeof(int));
    std::memcpy(&posY, (void *)((char *)byteCode + sizeof(int)), sizeof(int));
    std::memcpy(&multiplierAbscissa, (void *)((char *)byteCode + sizeof(int) * 2), sizeof(double));
    std::memcpy(&multiplierOrdinate, (void *)((char *)byteCode + sizeof(int) * 2 + sizeof(double)), sizeof(double));
    std::memcpy(&weight, (void *)((char *)byteCode + sizeof(int) * 2 + sizeof(double) * 2), sizeof(short));
    std::memcpy(
        &size_x, (void *)((char *)byteCode + sizeof(int) * 2 + sizeof(double) * 2 + sizeof(short)), sizeof(int));
    std::memcpy(
        &size_y, (void *)((char *)byteCode + sizeof(int) * 3 + sizeof(double) * 2 + sizeof(short)), sizeof(int));
    std::memcpy(
        &life, (void *)((char *)byteCode + sizeof(int) * 4 + sizeof(double) * 2 + sizeof(short)), sizeof(short));
    std::memcpy(&damage, (void *)((char *)byteCode + sizeof(int) * 4 + sizeof(double) * 2 + sizeof(short) * 2),
        sizeof(unsigned short));
    std::memcpy(&damageRadius,
        (void *)((char *)byteCode + sizeof(int) * 4 + sizeof(double) * 2 + sizeof(short) * 2 + sizeof(unsigned short)),
        sizeof(unsigned short));
    (void)posX;
    (void)posY;
    (void)multiplierAbscissa;
    (void)multiplierOrdinate;
    (void)weight;
    (void)size_x;
    (void)size_y;
    (void)life;
    (void)damage;
    (void)damageRadius;
    (void)uuid;
    (void)id;
    /// SEND THE NEW ENTITY TO ECS, WILL BE ADDED WHEN TRANSISTHOR WILL BE FULLY IMPLEMENTED
}

void Transisthor::entityConvertProjectileType(unsigned short id, void *byteCode)
{
    int posX = 0;
    int posY = 0;
    double velAbsc = 0;
    double velOrd = 0;
    unsigned short damage = 0;
    char *uuid = (char *)byteCode + sizeof(int) * 2 + sizeof(double) * 2 + sizeof(unsigned short);

    std::memcpy(&posX, byteCode, sizeof(int));
    std::memcpy(&posY, (void *)((char *)byteCode + sizeof(int)), sizeof(int));
    std::memcpy(&velAbsc, (void *)((char *)byteCode + sizeof(int) * 2), sizeof(double));
    std::memcpy(&velOrd, (void *)((char *)byteCode + sizeof(int) * 2 + sizeof(double)), sizeof(double));
    std::memcpy(&damage, (void *)((char *)byteCode + sizeof(int) * 2 + sizeof(double) * 2), sizeof(unsigned short));
    (void)posX;
    (void)posY;
    (void)velAbsc;
    (void)velOrd;
    (void)damage;
    (void)uuid;
    (void)id;
    /// SEND THE NEW ENTITY TO ECS, WILL BE ADDED WHEN TRANSISTHOR WILL BE FULLY IMPLEMENTED
}

void transisthor_lib::sendDataToAClientWithoutCommunicator(
    Communicator &communicator, Client &client, void *data, size_t size, unsigned short type)
{
    communicator.sendDataToAClient(client, data, size, type);
}
