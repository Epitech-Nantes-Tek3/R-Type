/*
** EPITECH PROJECT, 2022
** Project
** File description:
** Room
*/

/// @file Server/Room.cpp

#include "Room.hpp"
#include "Error/Error.hpp"

using namespace server_data;
using namespace error_lib;
using namespace communicator_lib;

Room::Room() : _communicatorInstance()
{
    _id = 0;
    _networkInformations = Client();
    _communicatorInstance = new Communicator(_networkInformations);
    _worldInstance = new World(1);
    _transisthorInstance = new Transisthor(*_communicatorInstance, *_worldInstance);
}

Room::Room(unsigned short id, Client networkInformations)
{
    _id = id;
    _networkInformations = networkInformations;
    _communicatorInstance = new Communicator(_networkInformations);
    _worldInstance = new World(1);
    _transisthorInstance = new Transisthor(*_communicatorInstance, *_worldInstance);
}

Room::~Room()
{
    delete _worldInstance;
    delete _communicatorInstance;
    delete _transisthorInstance;
}