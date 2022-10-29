/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** Server
*/

/// @file Server/Server.cpp

#include "Server.hpp"
#include "Error/Error.hpp"

using namespace server_data;
using namespace error_lib;
using namespace communicator_lib;

Server::Server(std::string address, unsigned short port)
{
    _activeRoomList = {};
    _networkInformations = Client(address, port);
    _state = HubState::UNDEFINED;
    _communicatorInstance = std::make_shared<Communicator>(_networkInformations);
}

Server::Server()
{
    _activeRoomList = {};
    _networkInformations = Client();
    _state = HubState::UNDEFINED;
    _communicatorInstance = std::make_shared<Communicator>(_networkInformations);
}

unsigned short Server::createANewRoom(std::string name)
{
    _activeRoomList.push_back(Room(_activeRoomList.size() + 1, name,
        Client(_networkInformations.getAddress(),
            _networkInformations.getPort()
                + 1000))); /// WILL BE REFACTO IN PART 2 TO AUTOMATIZE NEW FREE PORT DETECTION
    //_activeRoomList.back().startLobbyLoop();
    return _activeRoomList.size();
}

void Server::_startConnexionProtocol()
{
    _communicatorInstance.get()->startReceiverListening();
    _state = HubState::HUB;
}

void Server::startHubLoop()
{
    CommunicatorMessage connectionOperation;

    _startConnexionProtocol();
    while (_state != HubState::UNDEFINED && _state != HubState::ENDED) {
        try {
            connectionOperation = _communicatorInstance.get()->getLastMessage();
            if (connectionOperation.message.type == 14)
                _holdANewConnectionRequest(connectionOperation);
            if (connectionOperation.message.type == 13)
                _holdADisconnectionRequest(connectionOperation);
        } catch (NetworkError &error) {
        }
    }
    _disconnectionProcess();
}

void Server::_disconnectionProcess()
{
    auto clientList = _communicatorInstance.get()->getClientList();

    for (auto it : clientList)
        _communicatorInstance.get()->sendDataToAClient(it, nullptr, 0, 13);
}

void Server::_holdADisconnectionRequest(CommunicatorMessage disconnectionDemand)
{
    _communicatorInstance.get()->sendDataToAClient(disconnectionDemand.message.clientInfo, nullptr, 0, 13);
}

void Server::_holdANewConnectionRequest(CommunicatorMessage connectionDemand)
{
    void *networkData =
        std::malloc(sizeof(unsigned short) + _activeRoomList.size() * (sizeof(unsigned short) + sizeof(char) * 10));
    std::size_t offset = 0;
    unsigned short roomListSize = _activeRoomList.size();

    if (networkData == nullptr)
        throw std::logic_error("Malloc failed.");
    std::memcpy(networkData, &roomListSize, sizeof(unsigned short));
    offset += sizeof(unsigned short);
    for (auto it : _activeRoomList) {
        unsigned short roomId = it.getRoomId();
        std::string roomName = it.getRoomName();

        std::memcpy((void *)((char *)networkData + offset), &roomId, sizeof(unsigned short));
        offset += sizeof(unsigned short);
        std::memcpy((void *)((char *)networkData + offset), roomName.c_str(), sizeof(char) * 10);
        offset += sizeof(char) * 10;
    }
    _communicatorInstance.get()->sendDataToAClient(connectionDemand.message.clientInfo, networkData, offset, 15);
}

void Server::deleteARoom(unsigned short id)
{
    int pos = 0;

    for (auto i : _activeRoomList) {
        if (i.getRoomId() == id)
            _activeRoomList.erase(_activeRoomList.begin() + pos);
        pos++;
    }
}
