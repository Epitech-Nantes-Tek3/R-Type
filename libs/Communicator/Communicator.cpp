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

Communicator::Communicator() : _receiverModule(Receiver())
{
    _clientList = {};
    _senderModule = Sender();
}

Communicator::Communicator(Client networkBind) : _receiverModule(Receiver(networkBind))
{
    _clientList = {};
    _senderModule = Sender(networkBind.getPort());
}

void Communicator::addClientToList(Client &client)
{
    if (std::find(_clientList.begin(), _clientList.end(), client) != _clientList.end())
        throw std::invalid_argument("Client already registered in the communicator."); /// WILL BE REFACTOR WHEN ERROR GESTION IS IMPLEMENTED
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

CommunicatorMessage Communicator::getLastMessage(void)
{
    try {
        Message temp = _receiverModule.getLastMessage();
        try {
            addClientToList(temp.clientInfo);
            return CommunicatorMessage{temp, true};
        } catch (std::invalid_argument &error) {
            return CommunicatorMessage{temp, false};
        }
    } catch (std::invalid_argument &error) {
        throw std::invalid_argument("No message waiting."); /// TO REFACTO WHEN ERROR CLASS IS IMPLEMENTED
    }
}

CommunicatorMessage Communicator::getLastMessageFromClient(Client client)
{
    try {
        Message temp = _receiverModule.getLastMessageFromClient(client);
        try {
            addClientToList(temp.clientInfo);
            return CommunicatorMessage{temp, true};
        } catch (std::invalid_argument &error) {
            return CommunicatorMessage{temp, false};
        }
    } catch (std::invalid_argument &error) {
        throw std::invalid_argument("No message waiting."); /// TO REFACTO WHEN ERROR CLASS IS IMPLEMENTED
    }
}

void Communicator::kickAClient(Client client, Client newEndpoint)
{
    try {
        addClientToList(client);
        removeClientFromList(client);
        return;
    } catch (std::invalid_argument &error) {
    }
    if (newEndpoint == Client())
        _senderModule.sendDataToAClient(client, (void *)"kick", 5); /// TO REFACTO WHEN UDP PROTOCOL IS IMPLEMENTED
    else {
        unsigned short temp = newEndpoint.getPort();
        _senderModule.sendDataToAClient(client, &temp, 2); /// TO REFACTO WHEN UDP PROTOCOL IS IMPLEMENTED
    }
}

Communicator::~Communicator() {}
