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
}

void *Transisthor::transitNetworkDataToEcsData(Message networkData)
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

Client Transisthor::getClientByHisId(unsigned short id)
{
    (void) id;
    return Client();
}

void Transisthor::componentConvertDestinationType(unsigned short id, void *byteCode)
{
    Destination newComponent = buildComponentFromByteCode<Destination>(byteCode);

    (void)id;
    (void)newComponent;
    /// SEND THE NEW COMPONENT TO ECS, WILL BE ADDED WHEN TRANSISTHOR WILL BE FULLY IMPLEMENTED
}

void Transisthor::componentConvertEquipmentType(unsigned short id, void *byteCode)
{
    Equipment newComponent = buildComponentFromByteCode<Equipment>(byteCode);

    (void)id;
    (void)newComponent;
    /// SEND THE NEW COMPONENT TO ECS, WILL BE ADDED WHEN TRANSISTHOR WILL BE FULLY IMPLEMENTED
}

void Transisthor::componentConvertInvinsibleType(unsigned short id, void *byteCode)
{
    Invinsible newComponent = buildComponentFromByteCode<Invinsible>(byteCode);

    (void)id;
    (void)newComponent;
    /// SEND THE NEW COMPONENT TO ECS, WILL BE ADDED WHEN TRANSISTHOR WILL BE FULLY IMPLEMENTED
}

void Transisthor::componentConvertInvisibleType(unsigned short id, void *byteCode)
{
    Invisible newComponent = buildComponentFromByteCode<Invisible>(byteCode);

    (void)id;
    (void)newComponent;
    /// SEND THE NEW COMPONENT TO ECS, WILL BE ADDED WHEN TRANSISTHOR WILL BE FULLY IMPLEMENTED
}

void Transisthor::componentConvertLifeType(unsigned short id, void *byteCode)
{
    Life newComponent = buildComponentFromByteCode<Life>(byteCode);

    (void)id;
    (void)newComponent;
    /// SEND THE NEW COMPONENT TO ECS, WILL BE ADDED WHEN TRANSISTHOR WILL BE FULLY IMPLEMENTED
}

void Transisthor::componentConvertPositionType(unsigned short id, void *byteCode)
{
    Position newComponent = buildComponentFromByteCode<Position>(byteCode);

    (void)id;
    (void)newComponent;
    /// SEND THE NEW COMPONENT TO ECS, WILL BE ADDED WHEN TRANSISTHOR WILL BE FULLY IMPLEMENTED
}

void Transisthor::componentConvertVelocityType(unsigned short id, void *byteCode)
{
    Velocity newComponent = buildComponentFromByteCode<Velocity>(byteCode);

    (void)id;
    (void)newComponent;
    /// SEND THE NEW COMPONENT TO ECS, WILL BE ADDED WHEN TRANSISTHOR WILL BE FULLY IMPLEMENTED
}

void transisthor_lib::sendDataToAClientWithoutCommunicator(
    Communicator &communicator, Client &client, void *data, size_t size, unsigned short type)
{
    communicator.sendDataToAClient(client, data, size, type);
}