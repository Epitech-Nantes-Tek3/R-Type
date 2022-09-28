/*
** EPITECH PROJECT, 2022
** Project
** File description:
** Communicator
*/

/// @file libs/Communicator/Communicator.cpp

#include "Communicator.hpp"
#include <algorithm>
#include <iostream>

using namespace communicator_lib;

Communicator::Communicator()
{
    _clientList = {};
    _senderModule = Sender();
}

std::vector<Client> Communicator::getClientList(void) const { return _clientList; }

void Communicator::addClientToList(Client &client)
{
    if (std::find(_clientList.begin(), _clientList.end(), client) != _clientList.end()) {
        std::cerr << "Client already registered in the communicator." << std::endl;
        return;
    }
    _clientList.push_back(client);
}

void Communicator::removeClientFromList(Client &client)
{
    auto founded = std::find(_clientList.begin(), _clientList.end(), client);

    if (founded != _clientList.end())
        _clientList.erase(founded);
}

Client &Communicator::getClientFromList(std::string address, long port)
{
    Client temp = Client(address, port);
    auto founded = std::find(_clientList.begin(), _clientList.end(), temp);

    if (founded != _clientList.end())
        return *founded;
    /// THROW AN ERROR (REFACTO WHEN ERROR GESTION IS IMPLEMENTED)
    throw std::invalid_argument("Client not in the list.");
}

Communicator::~Communicator() {}
