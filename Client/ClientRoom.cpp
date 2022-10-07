/*
** EPITECH PROJECT, 2022
** Project
** File description:
** Client
*/

/// @file Client/ClientRoom.cpp

#include "ClientRoom.hpp"
#include "Error/Error.hpp"

using namespace error_lib;
using namespace communicator_lib;
using namespace client_data;

ClientRoom::ClientRoom()
{
    _networkInformations = Client();
    _communicatorInstance = std::make_shared<Communicator>(_networkInformations);
    _worldInstance = std::make_shared<World>(1);
    _transisthorInstance = std::make_shared<Transisthor>(*(_communicatorInstance.get()), *(_worldInstance.get()));
    _communicatorInstance.get()->updateTransisthorBridge(_transisthorInstance);
    _worldInstance.get()->updateTransisthorBridge(_communicatorInstance.get()->getTransisthorBridge());
    _state = ClientState::UNDEFINED;
}

ClientRoom::ClientRoom(std::string address, unsigned short port)
{
    _networkInformations = Client(address, port);
    _communicatorInstance = std::make_shared<Communicator>(_networkInformations);
    _worldInstance = std::make_shared<World>(1);
    _transisthorInstance = std::make_shared<Transisthor>(*(_communicatorInstance.get()), *(_worldInstance.get()));
    _communicatorInstance.get()->updateTransisthorBridge(_transisthorInstance);
    _worldInstance.get()->updateTransisthorBridge(_communicatorInstance.get()->getTransisthorBridge());
    _state = ClientState::UNDEFINED;
}
