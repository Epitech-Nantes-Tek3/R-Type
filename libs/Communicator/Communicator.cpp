/*
** EPITECH PROJECT, 2022
** Project
** File description:
** Communicator
*/

/// \file libs/Communicator/Communicator.cpp

#include "Communicator.hpp"
#include <iostream>
#include <algorithm>

using namespace communicator_lib;

Communicator::Communicator()
{
    client_list = {};
}

std::vector<Client> Communicator::getClientList(void) const {
    return client_list;
}

void Communicator::addClientToList(Client &client) {
    if (std::find(client_list.begin(), client_list.end(), client) != client_list.end()) {
        std::cerr << "Client already registered in the communicator." << std::endl;
        return;
    }
    client_list.push_back(client);
}

void Communicator::removeClientFromList(Client &client) {
    auto founded = std::find(client_list.begin(), client_list.end(), client);

    if (founded != client_list.end())
        client_list.erase(founded);
}

Client &Communicator::getClientFromList(std::string address, long port)
{
    Client temp = Client(address, port);
    auto founded = std::find(client_list.begin(), client_list.end(), temp);

    if (founded != client_list.end())
        return *founded;
    /// THROW AN ERROR (REFACTO WHEN ERROR GESTION IS IMPLEMENTED)
    throw std::invalid_argument("Client not in the list.");
}

Communicator::~Communicator()
{
}
