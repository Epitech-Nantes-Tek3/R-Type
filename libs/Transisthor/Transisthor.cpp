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

void *Transisthor::transitNetworkDataToEcsData(Message networkData)
{
    unsigned short id = 0;
    unsigned short type = 0;
    void *object = nullptr;

    std::memcpy(&id, networkData.data, sizeof(unsigned short));
    std::memcpy(&type, (void *)((char *)networkData.data + sizeof(unsigned short)), sizeof(unsigned short));
    object = (void *)((char *)networkData.data + sizeof(unsigned short) * 2);
    std::cerr << "Id : " << id << " Type : " << type << std::endl;
    return object;
}