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
    removeClientFromList(client);
    _receiverModule.removeAllClientMessage(client);
    std::cerr << "You have asked a client to switch to a new communicator." << std::endl;
}

void Communicator::sendProtocol20(Client client, Client newEndpoint)
{
    void *dataContent = std::malloc(sizeof(unsigned short) + newEndpoint.getAddress().size() * sizeof(char));
    unsigned short endpointPort = newEndpoint.getPort();

    if (dataContent == nullptr)
        throw error_lib::MallocError("Malloc failed.");
    std::memcpy(dataContent, &endpointPort, sizeof(unsigned short));
    std::memcpy((void *)((char *)dataContent + sizeof(unsigned short)), newEndpoint.getAddress().c_str(),
        newEndpoint.getAddress().size() * sizeof(char));
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

void Communicator::utilitarySendRoomConfiguration(std::string roomName, std::vector<short> configs, Client endpoint)
{
    Client temporaryClient;
    unsigned short nameSize = roomName.size();
    int size = sizeof(char) * nameSize + sizeof(short) * 6 + sizeof(unsigned short);
    void *networkObject = std::malloc(size);
    unsigned short offset = 0;

    if (networkObject == nullptr)
        throw MallocError("Malloc failed.");
    std::memcpy(networkObject, &nameSize, sizeof(unsigned short));
    offset += sizeof(unsigned short);
    std::memcpy((void *)((char *)networkObject + offset), roomName.c_str(), sizeof(char) * nameSize);
    offset += sizeof(char) * nameSize;
    for (int i = 0; i < 6; i++) {
        std::memcpy((void *)((char *)networkObject + sizeof(short) * i + offset), (void *)&configs[i], sizeof(short));
    }
    sendDataToAClient(endpoint, networkObject, size, 17);
    std::free(networkObject);
}

RoomConfiguration Communicator::utilitaryReceiveRoomConfiguration(CommunicatorMessage cryptedMessage)
{
    unsigned short roomNameLen = 0;
    char *roomName = nullptr;
    RoomConfiguration room;
    short offset = 0;

    std::memcpy(&roomNameLen, cryptedMessage.message.data, sizeof(unsigned short));
    offset += sizeof(unsigned short);
    roomName = (char *)cryptedMessage.message.data + offset;
    room.roomName = std::string(roomNameLen, '\0');
    for (int i = 0; i < roomNameLen; i++)
        room.roomName[i] = roomName[i];
    offset += sizeof(char) * roomNameLen;
    for (int i = 0; i < 6; i++) {
        std::memcpy((void *)&room.configs[i], (void *)((char *)cryptedMessage.message.data + offset), sizeof(short));
        offset += sizeof(short);
    }
    return room;
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
    std::free(networkObject);
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
    for (int i = 0; i < pseudoLen; i++)
        pseudoStr[i] = pseudo[i];
    offset += sizeof(char) * pseudoLen;
    messageContent = (char *)cryptedMessage.message.data + offset;
    messageLen = cryptedMessage.message.size - offset;
    std::string messageContentStr(messageLen, '\0');
    for (int i = 0; i < messageLen; i++)
        messageContentStr[i] = messageContent[i];
    return {pseudoStr, messageContentStr};
}

void Communicator::utilitaryAskForADatabaseValue(
    std::string pseudo, std::string key, std::vector<unsigned short> destination)
{
    Client temporaryClient;
    unsigned short pseudoSize = pseudo.size();
    void *networkObject = std::malloc(sizeof(char) * (pseudoSize + key.size()) + sizeof(unsigned short));
    unsigned short offset = 0;

    if (networkObject == nullptr)
        throw MallocError("Malloc failed.");
    std::memcpy((void *)((char *)networkObject + offset), &pseudoSize, sizeof(unsigned short));
    offset += sizeof(unsigned short);
    std::memcpy((void *)((char *)networkObject + offset), pseudo.c_str(), sizeof(char) * pseudoSize);
    offset += sizeof(char) * pseudoSize;
    std::memcpy((void *)((char *)networkObject + offset), key.c_str(), sizeof(char) * key.size());
    offset += sizeof(char) * key.size();
    for (auto it : destination) {
        temporaryClient = getClientByHisId(it);
        sendDataToAClient(temporaryClient, networkObject, offset, 40);
    }
    std::free(networkObject);
}

std::vector<std::string> Communicator::utilitaryReceiveAskingForDatabaseValue(CommunicatorMessage cryptedMessage)
{
    char *pseudo = nullptr;
    char *keyContent = nullptr;
    unsigned short keyLen = 0;
    unsigned short pseudoLen = 0;
    unsigned short offset = 0;

    std::memcpy(&pseudoLen, cryptedMessage.message.data, sizeof(unsigned short));
    offset += sizeof(unsigned short);
    pseudo = (char *)cryptedMessage.message.data + offset;
    std::string pseudoStr(pseudoLen, '\0');
    for (int i = 0; i < pseudoLen; i++)
        pseudoStr[i] = pseudo[i];
    offset += sizeof(char) * pseudoLen;
    keyContent = (char *)cryptedMessage.message.data + offset;
    keyLen = cryptedMessage.message.size - offset;
    std::string keyContentStr(keyLen, '\0');
    for (int i = 0; i < keyLen; i++)
        keyContentStr[i] = keyContent[i];
    return {pseudoStr, keyContentStr};
}

void Communicator::utilitaryAskForALeaderboard(std::string key, std::vector<unsigned short> destination)
{
    Client temporaryClient;
    void *networkObject = std::malloc(sizeof(char) * key.size());

    if (networkObject == nullptr)
        throw MallocError("Malloc failed.");
    std::memcpy(networkObject, key.c_str(), sizeof(char) * key.size());
    for (auto it : destination) {
        temporaryClient = getClientByHisId(it);
        sendDataToAClient(temporaryClient, networkObject, sizeof(char) * key.size(), 44);
    }
}

std::string Communicator::utilitaryReceiveScoreboardAsking(CommunicatorMessage cryptedMessage)
{
    char *key = (char *)cryptedMessage.message.data;
    std::string keyStr;

    keyStr.append(key, cryptedMessage.message.size);
    return keyStr;
}

void Communicator::utilitarySendALeaderboard(
    std::map<std::string, int> scoreboardContent, std::vector<unsigned short> destination)
{
    Client temporaryClient;
    unsigned short offset = 0;
    unsigned short scoreboardSize = scoreboardContent.size();
    void *networkObject = std::malloc(
        (sizeof(char) * 10 + sizeof(unsigned short) + sizeof(int)) * scoreboardSize + sizeof(unsigned short));

    if (networkObject == nullptr)
        throw MallocError("Malloc failed.");
    std::memcpy(networkObject, &scoreboardSize, sizeof(unsigned short));
    offset += sizeof(unsigned short);
    for (auto it : scoreboardContent) {
        unsigned short tempSize = it.first.size();
        int value = it.second;
        std::memcpy((void *)((char *)networkObject + offset), &tempSize, sizeof(unsigned short));
        offset += sizeof(unsigned short);
        std::memcpy((void *)((char *)networkObject + offset), it.first.c_str(), sizeof(char) * tempSize);
        offset += sizeof(char) * tempSize;
        std::memcpy((void *)((char *)networkObject + offset), &value, sizeof(int));
        offset += sizeof(int);
    }
    for (auto it : destination) {
        temporaryClient = getClientByHisId(it);
        sendDataToAClient(temporaryClient, networkObject, offset, 45);
    }
}

std::map<std::string, int> Communicator::utilitaryReceiveScoreboard(CommunicatorMessage cryptedMessage)
{
    unsigned short scoreboardSize = 0;
    unsigned short offset = 0;
    std::map<std::string, int> scoreboard;

    std::memcpy(&scoreboardSize, cryptedMessage.message.data, sizeof(unsigned short));
    offset += sizeof(unsigned short);
    for (int i = 0; i < scoreboardSize; i++) {
        unsigned short pseudoSize = 0;
        std::string pseudoStr;
        int value = 0;

        std::memcpy(&pseudoSize, (void *)((char *)cryptedMessage.message.data + offset), sizeof(unsigned short));
        offset += sizeof(unsigned short);
        char *pseudo = (char *)cryptedMessage.message.data + offset;
        pseudoStr.append(pseudo, pseudoSize);
        offset += sizeof(char) * pseudoSize;
        std::memcpy(&value, (void *)((char *)cryptedMessage.message.data + offset), sizeof(int));
        offset += sizeof(int);
        scoreboard[pseudoStr] = value;
    }
    return scoreboard;
}

void Communicator::utilitarySendDatabaseValue(std::string value, Client &destination)
{
    void *networkObject = std::malloc(sizeof(char) * (value.size()));

    if (networkObject == nullptr)
        throw MallocError("Malloc failed.");
    std::memcpy(networkObject, value.c_str(), sizeof(char) * value.size());
    sendDataToAClient(destination, networkObject, sizeof(char) * (value.size()), 41);
    std::free(networkObject);
}

void Communicator::utilitarySetADatabaseValue(
    std::string pseudo, unsigned short key, std::string value, std::vector<unsigned short> destination)
{
    Client temporaryClient;
    unsigned short pseudoSize = pseudo.size();
    unsigned short offset = 0;
    void *networkObject = std::malloc(sizeof(char) * (pseudoSize + value.size()) + sizeof(unsigned short) * 2);

    if (networkObject == nullptr)
        throw MallocError("Malloc failed.");
    std::memcpy(networkObject, &pseudoSize, sizeof(unsigned short));
    offset += sizeof(unsigned short);
    std::memcpy((void *)((char *)networkObject + offset), pseudo.c_str(), sizeof(char) * pseudoSize);
    offset += sizeof(char) * pseudoSize;
    std::memcpy((void *)((char *)networkObject + offset), &key, sizeof(unsigned short));
    offset += sizeof(unsigned short);
    std::memcpy((void *)((char *)networkObject + offset), value.c_str(), sizeof(char) * value.size());
    offset += sizeof(char) * value.size();
    for (auto it : destination) {
        temporaryClient = getClientByHisId(it);
        sendDataToAClient(temporaryClient, networkObject, offset, 42);
    }
    std::free(networkObject);
}

std::vector<std::string> Communicator::utilitaryReceiveSetDatabaseValue(CommunicatorMessage cryptedMessage)
{
    char *pseudo = nullptr;
    unsigned short pseudoSize = 0;
    unsigned short key = 0;
    char *value = nullptr;
    unsigned short offset = 0;

    std::memcpy(&pseudoSize, cryptedMessage.message.data, sizeof(unsigned short));
    offset += sizeof(unsigned short);
    pseudo = (char *)cryptedMessage.message.data + offset;
    std::string pseudoStr(pseudoSize, '\0');
    for (int i = 0; i < pseudoSize; i++)
        pseudoStr[i] = pseudo[i];
    offset += sizeof(char) * pseudoSize;
    std::memcpy(&key, (void *)((char *)cryptedMessage.message.data + offset), sizeof(unsigned short));
    offset += sizeof(unsigned short);
    value = (char *)cryptedMessage.message.data + offset;
    std::size_t valueSize = cryptedMessage.message.size - offset;
    std::string valueStr;
    if (key == 4 || key == 5) {
        valueStr = std::string(valueSize + 2, '\'');
        for (std::size_t i = 1; i < valueSize + 1; i++)
            valueStr[i] = value[i - 1];
    } else {
        valueStr = std::string(valueSize, '\0');
        for (std::size_t i = 0; i < valueSize; i++)
            valueStr[i] = value[i];
    }
    return {pseudoStr, std::to_string(key), valueStr};
}

std::string Communicator::utilitaryReceiveDatabaseValue(CommunicatorMessage cryptedMessage)
{
    char *valueContent = nullptr;

    valueContent = (char *)cryptedMessage.message.data;
    return std::string(valueContent);
}
