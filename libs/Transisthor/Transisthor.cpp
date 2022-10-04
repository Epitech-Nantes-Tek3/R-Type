/*
** EPITECH PROJECT, 2022
** Project
** File description:
** Transisthor
*/

/// @file libs/Transisthor/Transisthor.cpp

#include "Transisthor.hpp"
#include "Error/Error.hpp"

using namespace transisthor_lib;
using namespace error_lib;

Transisthor::Transisthor(Communicator &communicator, World &ecsWorld) : _communicator(communicator), _ecsWorld(ecsWorld)
{
    _componentConvertFunctionList[1] =
        std::bind(&Transisthor::componentConvertPositionType, this, std::placeholders::_1, std::placeholders::_2);
}

void *Transisthor::transitNetworkDataToEcsData(Message networkData)
{
    unsigned short id = 0;
    unsigned short type = 0;
    void *object = nullptr;

    std::memcpy(&id, networkData.data, sizeof(unsigned short));
    std::memcpy(&type, (void *)((char *)networkData.data + sizeof(unsigned short)), sizeof(unsigned short));
    object = (void *)((char *)networkData.data + sizeof(unsigned short) * 2);
    std::cerr << "Id : " << id << " Type : " << type << std::endl;
    if (_componentConvertFunctionList.find(type) == _componentConvertFunctionList.end())
        return object; /// THROW ERROR INVALID TYPE
    _componentConvertFunctionList[type](id, object);
    return object; /// ONLY USED FOR UNIT TESTING
}

void Transisthor::componentConvertPositionType(unsigned short id, void *byteCode)
{
    Position newComponent = buildComponentFromByteCode<Position>(byteCode);

    (void)id;
    (void)newComponent;
    /// SEND THE NEW COMPONENT TO ECS, WILL BE ADDED WHEN TRANSISTHOR WILL BE FULLY IMPLEMENTED
}