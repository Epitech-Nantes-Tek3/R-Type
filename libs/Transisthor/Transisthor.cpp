/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** Transisthor
*/

/// @file libs/Transisthor/Transisthor.cpp

#include "Transisthor.hpp"
#include "Error/Error.hpp"
#include "TransisthorECSLogic/Both/Components/Networkable.hpp"
#include "TransisthorECSLogic/Server/Resources/NetworkableIdGenerator.hpp"
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
#include "R-TypeLogic/Server/Components/AfkFrequencyComponent.hpp"
#include <boost/asio/thread_pool.hpp>

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
    _componentConvertFunctionList[8] =
        std::bind(&Transisthor::componentConvertDeathType, this, std::placeholders::_1, std::placeholders::_2);
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
        transisthor_lib::sendDataToAClientWithoutCommunicator(_communicator, temporaryClient, networkObject,
            (sizeof(unsigned short) * 3 + sizeof(char) * uuid.size()), 31);
    }
    return networkObject;
}

void *Transisthor::transitEcsDataToNetworkDataEntityEnemy(unsigned short id, int posX, int posY,
    double multiplierAbscissa, double multiplierOrdinate, short weight, int sizeX, int sizeY, short life,
    unsigned short damage, unsigned short damageRadius, std::string uuid, std::vector<unsigned short> destination)
{
    void *networkObject = std::malloc((sizeof(unsigned short) * 4 + sizeof(int) * 4 + sizeof(double) * 2
        + sizeof(short) * 2 + sizeof(char) * uuid.size()));
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
        &sizeX, sizeof(int));
    std::memcpy((void *)((char *)networkObject + sizeof(unsigned short) * 2 + sizeof(int) * 3 + sizeof(double) * 2
                    + sizeof(short)),
        &sizeY, sizeof(int));
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
            (sizeof(unsigned short) * 4 + sizeof(int) * 4 + sizeof(double) * 2 + sizeof(short) * 2
                + sizeof(char) * uuid.size()),
            31);
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
        transisthor_lib::sendDataToAClientWithoutCommunicator(_communicator, temporaryClient, networkObject,
            (sizeof(unsigned short) * 3 + sizeof(char) * uuid.size()), 31);
    }
    return networkObject;
}

void *Transisthor::transitEcsDataToNetworkDataEntityObstacle(unsigned short id, int posX, int posY,
    unsigned short damage, std::string uuid, std::vector<unsigned short> destination)
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
        transisthor_lib::sendDataToAClientWithoutCommunicator(_communicator, temporaryClient, networkObject,
            (sizeof(unsigned short) * 3 + sizeof(int) * 2 + sizeof(char) * uuid.size()), 31);
    }
    return networkObject;
}

void *Transisthor::transitEcsDataToNetworkDataEntityPlayer(unsigned short id, int posX, int posY,
    double multiplierAbscissa, double multiplierOrdinate, short weight, int sizeX, int sizeY, short life,
    unsigned short damage, unsigned short damageRadius, bool isControlable, unsigned short playerIdentifier,
    std::string uuid, std::vector<unsigned short> destination)
{
    void *networkObject = std::malloc((sizeof(unsigned short) * 5 + sizeof(int) * 4 + sizeof(double) * 2
        + sizeof(short) * 2 + sizeof(char) * uuid.size() + sizeof(bool)));
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
        &sizeX, sizeof(int));
    std::memcpy((void *)((char *)networkObject + sizeof(unsigned short) * 2 + sizeof(int) * 3 + sizeof(double) * 2
                    + sizeof(short)),
        &sizeY, sizeof(int));
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
        &isControlable, sizeof(bool));
    std::memcpy((void *)((char *)networkObject + sizeof(unsigned short) * 4 + sizeof(int) * 4 + sizeof(double) * 2
                    + sizeof(short) * 2 + sizeof(bool)),
        &playerIdentifier, sizeof(unsigned short));
    std::memcpy((void *)((char *)networkObject + sizeof(unsigned short) * 5 + sizeof(int) * 4 + sizeof(double) * 2
                    + sizeof(short) * 2 + sizeof(bool)),
        uuid.c_str(), sizeof(char) * uuid.size());
    for (auto it : destination) {
        temporaryClient = getClientByHisId(it);
        transisthor_lib::sendDataToAClientWithoutCommunicator(_communicator, temporaryClient, networkObject,
            (sizeof(unsigned short) * 5 + sizeof(int) * 4 + sizeof(double) * 2 + sizeof(short) * 2
                + sizeof(char) * uuid.size() + sizeof(bool)),
            31);
    }
    return networkObject;
}

void *Transisthor::transitEcsDataToNetworkDataEntityProjectile(unsigned short id, int posX, int posY, double velAbsc,
    double velOrd, unsigned short damage, std::string uuid, std::vector<unsigned short> destination)
{
    void *networkObject =
        std::malloc((sizeof(unsigned short) * 3 + sizeof(int) * 2 + sizeof(double) * 2 + sizeof(char) * uuid.size()));
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
    std::vector<std::shared_ptr<ecs::Entity>> joined = _ecsWorld.joinEntities<Player>();
    for (auto it : joined) {
        if (it->getComponent<Networkable>().id == id) {
            it->getComponent<AfkFrequency>().frequency = it->getComponent<AfkFrequency>().baseFrequency;
            return;
        }
    }
}

void Transisthor::componentConvertDeathType(unsigned short id, void *byteCode)
{
    Death newComponent = buildComponentFromByteCode<Death>(byteCode);

    _ecsWorld.updateComponentOfAnEntityFromGivenDistinctiveComponent<Networkable, Death>(Networkable(id), newComponent);
}

void Transisthor::entityConvertAlliedProjectileType(unsigned short id, void *byteCode)
{
    unsigned short allyId = 0;
    char *uuid = (char *)byteCode + sizeof(unsigned short);

    std::memcpy(&allyId, byteCode, sizeof(unsigned short));
    std::vector<std::shared_ptr<Entity>> networkables = _ecsWorld.joinEntities<Networkable>();

    auto findShooter = [allyId](std::vector<std::shared_ptr<Entity>> networkables) {
        for (std::shared_ptr<Entity> ptr : networkables) {
            std::lock_guard(*ptr.get());
            if (ptr->getComponent<Networkable>().id == allyId)
                return ptr;
        }
        throw NetworkError("The entity was not found");
    };
    std::shared_ptr<Entity> shooter;
    try {
        shooter = findShooter(networkables);
    } catch (const NetworkError &e) {
        std::cerr << "Parent entities cannot be found." << std::endl;
        return;
    }

    if (uuid != nullptr && id == 0) {
        uuid[16] = '\0';
        createNewAlliedProjectile(_ecsWorld, *(shooter.get()), uuid,
            _ecsWorld.getResource<NetworkableIdGenerator>().generateNewNetworkableId());
        shooter->getComponent<AfkFrequency>().frequency = shooter->getComponent<AfkFrequency>().baseFrequency;
    } else {
        std::size_t entityId;
        if (uuid == nullptr) {
            entityId = createNewAlliedProjectile(_ecsWorld, *(shooter.get()));
            ecs::Entity &entity = _ecsWorld.getEntity(entityId);
            auto guard = std::lock_guard(entity);
            entity.getComponent<Networkable>() = id;
        } else {
            std::vector<std::shared_ptr<Entity>> newlyCreated = _ecsWorld.joinEntities<NewlyCreated>();
            uuid[16] = '\0';
            for (std::shared_ptr<Entity> ptr : newlyCreated) {
                std::lock_guard(*ptr.get());
                if (ptr->getComponent<NewlyCreated>().uuid == uuid) {
                    ptr->getComponent<NewlyCreated>().uuid = "";
                    ptr->getComponent<Networkable>().id = id;
                    entityId = ptr->getId();
                    break;
                }
            }
        }
    }
}

void Transisthor::entityConvertEnemyType(unsigned short id, void *byteCode)
{
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
    char *uuid =
        (char *)byteCode + sizeof(int) * 4 + sizeof(double) * 2 + sizeof(short) * 2 + sizeof(unsigned short) * 2;

    std::memcpy(&posX, byteCode, sizeof(int));
    std::memcpy(&posY, (void *)((char *)byteCode + sizeof(int)), sizeof(int));
    std::memcpy(&multiplierAbscissa, (void *)((char *)byteCode + sizeof(int) * 2), sizeof(double));
    std::memcpy(&multiplierOrdinate, (void *)((char *)byteCode + sizeof(int) * 2 + sizeof(double)), sizeof(double));
    std::memcpy(&weight, (void *)((char *)byteCode + sizeof(int) * 2 + sizeof(double) * 2), sizeof(short));
    std::memcpy(&sizeX, (void *)((char *)byteCode + sizeof(int) * 2 + sizeof(double) * 2 + sizeof(short)), sizeof(int));
    std::memcpy(&sizeY, (void *)((char *)byteCode + sizeof(int) * 3 + sizeof(double) * 2 + sizeof(short)), sizeof(int));
    std::memcpy(
        &life, (void *)((char *)byteCode + sizeof(int) * 4 + sizeof(double) * 2 + sizeof(short)), sizeof(short));
    std::memcpy(&damage, (void *)((char *)byteCode + sizeof(int) * 4 + sizeof(double) * 2 + sizeof(short) * 2),
        sizeof(unsigned short));
    std::memcpy(&damageRadius,
        (void *)((char *)byteCode + sizeof(int) * 4 + sizeof(double) * 2 + sizeof(short) * 2 + sizeof(unsigned short)),
        sizeof(unsigned short));

    std::string uuidStr(uuid);
    if (uuidStr != "" && id == 0) {
        createNewEnemy(_ecsWorld, posX, posY, multiplierAbscissa, multiplierOrdinate, weight, sizeX, sizeY, life,
            damage, damageRadius, "", _ecsWorld.getResource<NetworkableIdGenerator>().generateNewNetworkableId());
    } else {
        ecs::Entity &entity = _ecsWorld.getEntity(createNewEnemy(_ecsWorld, posX, posY, multiplierAbscissa,
            multiplierOrdinate, weight, sizeX, sizeY, life, damage, damageRadius));
        auto guard = std::lock_guard(entity);
        entity.addComponent<Networkable>(id);
    }
}

void Transisthor::entityConvertEnemyProjectileType(unsigned short id, void *byteCode)
{
    unsigned short enemyId = 0;
    char *uuid = (char *)byteCode + sizeof(unsigned short);

    std::memcpy(&enemyId, byteCode, sizeof(unsigned short));
    std::vector<std::shared_ptr<Entity>> networkables = _ecsWorld.joinEntities<Networkable>();

    auto findShooter = [enemyId](std::vector<std::shared_ptr<Entity>> networkables) {
        for (std::shared_ptr<Entity> ptr : networkables) {
            std::lock_guard(*ptr.get());
            if (ptr->getComponent<Networkable>().id == enemyId)
                return ptr;
        }
        throw NetworkError("The entity was not found");
    };
    std::shared_ptr<Entity> shooter;
    try {
        shooter = findShooter(networkables);
    } catch (const NetworkError &e) {
        std::cerr << "Parent entities cannot be found." << std::endl;
        return;
    }

    std::string uuidStr(uuid);
    if (uuidStr != "" && id == 0) {
        createNewEnemyProjectile(
            _ecsWorld, shooter, "", _ecsWorld.getResource<NetworkableIdGenerator>().generateNewNetworkableId());
    } else {
        ecs::Entity &entity = _ecsWorld.getEntity(createNewEnemyProjectile(_ecsWorld, shooter));
        auto guard = std::lock_guard(entity);
        entity.addComponent<Networkable>(id);
    }
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

    std::string uuidStr(uuid);

    if (uuidStr != "" && id == 0) {
        createNewObstacle(_ecsWorld, posX, posY, damage, "",
            _ecsWorld.getResource<NetworkableIdGenerator>().generateNewNetworkableId());
    } else {
        ecs::Entity &entity = _ecsWorld.getEntity(createNewObstacle(_ecsWorld, posX, posY, damage));
        auto guard = std::lock_guard(entity);
        entity.addComponent<Networkable>(id);
    }
}

void Transisthor::entityConvertPlayerType(unsigned short id, void *byteCode)
{
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
    bool isPlayer = false;
    unsigned short playerIdentifier = 0;
    char *uuid = (char *)byteCode + sizeof(int) * 4 + sizeof(double) * 2 + sizeof(short) * 2
        + sizeof(unsigned short) * 3 + sizeof(bool);

    std::memcpy(&posX, byteCode, sizeof(int));
    std::memcpy(&posY, (void *)((char *)byteCode + sizeof(int)), sizeof(int));
    std::memcpy(&multiplierAbscissa, (void *)((char *)byteCode + sizeof(int) * 2), sizeof(double));
    std::memcpy(&multiplierOrdinate, (void *)((char *)byteCode + sizeof(int) * 2 + sizeof(double)), sizeof(double));
    std::memcpy(&weight, (void *)((char *)byteCode + sizeof(int) * 2 + sizeof(double) * 2), sizeof(short));
    std::memcpy(&sizeX, (void *)((char *)byteCode + sizeof(int) * 2 + sizeof(double) * 2 + sizeof(short)), sizeof(int));
    std::memcpy(&sizeY, (void *)((char *)byteCode + sizeof(int) * 3 + sizeof(double) * 2 + sizeof(short)), sizeof(int));
    std::memcpy(
        &life, (void *)((char *)byteCode + sizeof(int) * 4 + sizeof(double) * 2 + sizeof(short)), sizeof(short));
    std::memcpy(&damage, (void *)((char *)byteCode + sizeof(int) * 4 + sizeof(double) * 2 + sizeof(short) * 2),
        sizeof(unsigned short));
    std::memcpy(&damageRadius,
        (void *)((char *)byteCode + sizeof(int) * 4 + sizeof(double) * 2 + sizeof(short) * 2 + sizeof(unsigned short)),
        sizeof(unsigned short));
    std::memcpy(&isPlayer,
        (void *)((char *)byteCode + sizeof(int) * 4 + sizeof(double) * 2 + sizeof(short) * 2
            + sizeof(unsigned short) * 2),
        sizeof(bool));
    std::memcpy(&playerIdentifier,
        (void *)((char *)byteCode + sizeof(int) * 4 + sizeof(double) * 2 + sizeof(short) * 2
            + sizeof(unsigned short) * 2 + sizeof(bool)),
        sizeof(unsigned short));

    std::string uuidStr(uuid);

    if (uuidStr != "" && id == 0) {
        createNewPlayer(_ecsWorld, posX, posY, multiplierAbscissa, multiplierOrdinate, weight, sizeX, sizeY, life,
            damage, damageRadius, false, playerIdentifier, "",
            _ecsWorld.getResource<NetworkableIdGenerator>().generateNewNetworkableId());
    } else {
        ecs::Entity &entity = _ecsWorld.getEntity(createNewPlayer(_ecsWorld, posX, posY, multiplierAbscissa,
            multiplierOrdinate, weight, sizeX, sizeY, life, damage, damageRadius, isPlayer, playerIdentifier));
        auto guard = std::lock_guard(entity);
        entity.addComponent<Networkable>(id);
    }
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

    std::string uuidStr(uuid);

    if (uuidStr != "" && id == 0) {
        createNewProjectile(_ecsWorld, posX, posY, velAbsc, velOrd, damage, "",
            _ecsWorld.getResource<NetworkableIdGenerator>().generateNewNetworkableId());
    } else {
        ecs::Entity &entity = _ecsWorld.getEntity(createNewProjectile(_ecsWorld, posX, posY, velAbsc, velOrd, damage));
        auto guard = std::lock_guard(entity);
        entity.addComponent<Networkable>(id);
    }
}

void transisthor_lib::sendDataToAClientWithoutCommunicator(
    Communicator &communicator, Client &client, void *data, size_t size, unsigned short type)
{
    communicator.sendDataToAClient(client, data, size, type);
}
