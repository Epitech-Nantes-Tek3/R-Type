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
    _transisthorBridge = std::shared_ptr<Transisthor>(nullptr);
}

Communicator::Communicator(Client networkBind) : _receiverModule(Receiver(networkBind))
{
    _clientList = {};
    _senderModule = Sender(networkBind.getPort());
    _transisthorBridge = std::shared_ptr<Transisthor>(nullptr);
}

void Communicator::addClientToList(Client &client)
{
    if (std::find(_clientList.begin(), _clientList.end(), client) != _clientList.end())
        throw NetworkError("Client already registered in the communicator.", "Communicator.cpp -> addClientToList");
    client.setId(_clientList.size());
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
        Message lastMessage = _receiverModule.getLastMessage();
        receiveProtocol2X(lastMessage);
        receiveProtocol3X(lastMessage);
        try {
            addClientToList(lastMessage.clientInfo);
            return CommunicatorMessage{lastMessage, true};
        } catch (NetworkError &error) {
            return CommunicatorMessage{lastMessage, false};
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
    if (newEndpoint == Client()) {
        _senderModule.sendDataToAClient(client, (void *)"kick", 5, 30); /// TO REFACTO WHEN UDP PROTOCOL IS IMPLEMENTED
        return;
    }
    sendProtocol20(client, newEndpoint);
    std::cerr << "Removed : " << client.getId() << std::endl;
    removeClientFromList(client);
    _receiverModule.removeAllClientMessage(client);
    std::cerr << "You have asked a client to switch to a new communicator." << std::endl;
}

void Communicator::sendProtocol20(Client client, Client newEndpoint)
{
    void *dataContent = std::malloc(sizeof(void *) * (sizeof(unsigned short) + newEndpoint.getAddress().size()));
    unsigned short endpointPort = newEndpoint.getPort();

    if (dataContent == nullptr)
        throw error_lib::MallocError("Malloc failed.");
    std::memcpy(dataContent, &endpointPort, sizeof(unsigned short));
    std::memcpy((void *)((char *)dataContent + sizeof(unsigned short)), newEndpoint.getAddress().data(),
        newEndpoint.getAddress().size());
    _senderModule.sendDataToAClient(
        client, dataContent, sizeof(unsigned short) + newEndpoint.getAddress().size() * sizeof(char), 20);
}

void Communicator::receiveProtocol2X(Message lastMessage)
{
    if (lastMessage.type == 21) {
        addClientToList(lastMessage.clientInfo);
        std::cerr << "A new client has been transfered to your communicator." << std::endl;
        throw NetworkError("No message waiting for traitment.", "Communicator.cpp -> getLastMessage");
    }
    if (lastMessage.type == 20) {
        replaceClientByAnother(_receiverModule.getLastMessage().clientInfo, lastMessage.clientInfo);
        std::cerr << "You have been asked to switch to a new communicator." << std::endl;
        _senderModule.sendDataToAClient(lastMessage.clientInfo, nullptr, 0, 21);
    }
}

void Communicator::receiveProtocol3X(Message lastMessage)
{
    if (lastMessage.type == 30) {
        _transisthorBridge.get()->transitNetworkDataToEcsDataComponent(lastMessage);
        throw NetworkError("No message waiting for traitment.", "Communicator.cpp -> receiveProtocol3X");
    }
    if (lastMessage.type == 31) {
        _transisthorBridge.get()->transitNetworkDataToEcsDataEntity(lastMessage);
        throw NetworkError("No message waiting for traitment.", "Communicator.cpp -> receiveProtocol3X");
    }
}

void Communicator::replaceClientByAnother(Client oldClient, Client newClient)
{
    removeClientFromList(oldClient);
    addClientToList(newClient);
    _receiverModule.removeAllClientMessage(oldClient);
}

Client Communicator::getClientByHisId(unsigned short id)
{
    for (auto it : _clientList) {
        if (it.getId() == id)
            return it;
    }
    throw NetworkError("No matched client founded.", "Communicator.cpp -> getClientByHisId");
}

unsigned short Communicator::getServerEndpointId(void)
{
    if (_clientList.size() != 1)
        throw NetworkError("You are not inside a client communicator. No server can be found.",
            "Communicator.cpp -> getServerEndpointId");
    return _clientList.at(0).getId();
}

void Communicator::utilitarySendChatMessage(
    std::string pseudo, std::string messageContent, std::vector<unsigned short> destination)
{
    Client temporaryClient;
    void *networkObject = std::malloc(sizeof(char) * (pseudo.size() + messageContent.size()) + sizeof(unsigned short));
    unsigned short pseudoLen = pseudo.size();

    if (networkObject == nullptr)
        throw MallocError("Malloc failed.");
    std::memcpy(networkObject, &pseudoLen, sizeof(unsigned short));
    std::memcpy((void *)((char *)networkObject + sizeof(unsigned short)), pseudo.c_str(), sizeof(char) * pseudoLen);
    std::memcpy((void *)((char *)networkObject + sizeof(unsigned short) + sizeof(char) * pseudoLen),
        messageContent.c_str(), sizeof(char) * messageContent.size());
    for (auto it : destination) {
        temporaryClient = getClientByHisId(it);
        sendDataToAClient(temporaryClient, networkObject,
            sizeof(unsigned short) + sizeof(char) * (pseudo.size() + messageContent.size()), 50);
    }
}

std::vector<std::string> Communicator::utilitaryReceiveChatMessage(CommunicatorMessage cryptedMessage)
{
    char *pseudo = nullptr;
    char *messageContent = nullptr;
    unsigned short pseudoLen = 0;
    unsigned short messageLen = 0;
    unsigned short offset = 0;

    std::memcpy(&pseudoLen, cryptedMessage.message.data, sizeof(unsigned short));
    offset += sizeof(unsigned short);
    pseudo = (char *)cryptedMessage.message.data + offset;
    std::string pseudoStr(pseudoLen, '\0');
    for(int i = 0; i < pseudoLen; i++)
        pseudoStr[i] = pseudo[i];
    offset += sizeof(char) * pseudoLen;
    messageContent = (char *)cryptedMessage.message.data + offset;
    messageLen = cryptedMessage.message.size - offset;
    std::string messageContentStr(messageLen, '\0');
    for(int i = 0; i < messageLen; i++)
        messageContentStr[i] = messageContent[i];
    return {pseudoStr, messageContentStr};
}

Communicator::~Communicator() {}
