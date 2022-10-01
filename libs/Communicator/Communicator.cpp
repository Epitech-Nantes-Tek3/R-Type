/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** Communicator
*/

/// @file libs/Communicator/Communicator.cpp

#include "Communicator.hpp"
#include <algorithm>
#include <iostream>
#include "Error/Error.hpp"

using namespace communicator_lib;
using namespace error_lib;

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
        throw NetworkError("Client already registered in the communicator.", "Communicator.cpp -> addClientToList");
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
    throw NetworkError("The wanted client are not in the list.", "Communicator.cpp -> getClientFromList");
}

CommunicatorMessage Communicator::getLastMessage(void)
{
    try {
        Message temp = _receiverModule.getLastMessage();
        try {
            addClientToList(temp.clientInfo);
            return CommunicatorMessage{temp, true};
        } catch (NetworkError &error) {
            return CommunicatorMessage{temp, false};
        }
    } catch (NetworkError &error) {
        throw NetworkError("No message waiting for traitment.", "Communicator.cpp -> getLastMessage");
    }
}

CommunicatorMessage Communicator::getLastMessageFromClient(Client client)
{
    try {
        Message temp = _receiverModule.getLastMessageFromClient(client);
        try {
            addClientToList(temp.clientInfo);
            return CommunicatorMessage{temp, true};
        } catch (NetworkError &error) {
            return CommunicatorMessage{temp, false};
        }
    } catch (NetworkError &error) {
        throw NetworkError(
            "This client has no message waiting for traitment.", "Communicator.cpp -> getLastMessageFromClient");
    }
}

void Communicator::kickAClient(Client client, Client newEndpoint)
{
    try {
        addClientToList(client);
        removeClientFromList(client);
        return;
    } catch (NetworkError &error) {
    }
    if (newEndpoint == Client())
        _senderModule.sendDataToAClient(client, (void *)"kick", 5, 30); /// TO REFACTO WHEN UDP PROTOCOL IS IMPLEMENTED
    else {
        unsigned short temp = newEndpoint.getPort();
        _senderModule.sendDataToAClient(client, &temp, 2, 30); /// TO REFACTO WHEN UDP PROTOCOL IS IMPLEMENTED
    }
}

Communicator::~Communicator() {}
