/*
** EPITECH PROJECT, 2022
** Project
** File description:
** Client
*/

/// @file Client/Client.cpp

#include "Client.hpp"
#include "Error/Error.hpp"

using namespace client_data;
using namespace error_lib;
using namespace communicator_lib;

Client::Client()
{
    _networkInformations = Client();
    _communicatorInstance = std::make_shared<Communicator>(_networkInformations);
    _worldInstance = std::make_shared<World>(1);
    _transisthorInstance = std::make_shared<Transisthor>(*(_communicatorInstance.get()), *(_worldInstance.get()));
    _communicatorInstance.get()->updateTransisthorBridge(_transisthorInstance);
    _worldInstance.get()->updateTransisthorBridge(_communicatorInstance.get()->getTransisthorBridge());
    _state = ClientState::UNDEFINED;
}

Client::Client(Client networkInformations)
{
    _networkInformations = networkInformations;
    _communicatorInstance = std::make_shared<Communicator>(_networkInformations);
    _worldInstance = std::make_shared<World>(1);
    _transisthorInstance = std::make_shared<Transisthor>(*(_communicatorInstance.get()), *(_worldInstance.get()));
    _communicatorInstance.get()->updateTransisthorBridge(_transisthorInstance);
    _worldInstance.get()->updateTransisthorBridge(_communicatorInstance.get()->getTransisthorBridge());
    _state = ClientState::UNDEFINED;
}
