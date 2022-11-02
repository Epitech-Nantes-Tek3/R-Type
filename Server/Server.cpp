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

unsigned short Server::_getAFreePort(unsigned short actual)
{
    try {
        boost::asio::io_service io_service;
        boost::asio::ip::udp::socket socket(io_service);
        socket.open(boost::asio::ip::udp::v4());
        socket.bind(boost::asio::ip::udp::endpoint(
            boost::asio::ip::address::from_string(_networkInformations.getAddress()), actual));
        return actual;
    } catch (const boost::system::system_error &error) {
        return _getAFreePort(actual + 101);
    }
}

unsigned short Server::createANewRoom(std::string name)
{
    _activeRoomList.push_back(Room(_activeRoomList.size() + 1, name,
        Client(_networkInformations.getAddress(), _getAFreePort(_networkInformations.getPort() + 101))));
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
            if (connectionOperation.message.type == 13)
                _holdADisconnectionRequest(connectionOperation);
            if (connectionOperation.message.type == 14)
                _holdANewConnectionRequest(connectionOperation);
            if (connectionOperation.message.type == 16)
                _holdAJoinRoomRequest(connectionOperation);
            if (connectionOperation.message.type == 17)
                _holdACreateRoomRequest(connectionOperation);
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

void Server::_holdAJoinRoomRequest(CommunicatorMessage joinDemand)
{
    unsigned short choosenRoom = 0;

    std::memcpy(&choosenRoom, joinDemand.message.data, sizeof(unsigned short));
    for (auto it : _activeRoomList) {
        if (it == choosenRoom) {
            _communicatorInstance.get()->kickAClient(joinDemand.message.clientInfo, it.getNetworkInformations());
            it.startLobbyLoop(); /// WILL BE REMOVED WITH PROCESS IMPLEMENTATION
            return;
        }
    }
    _communicatorInstance.get()->sendDataToAClient(joinDemand.message.clientInfo, nullptr, 0, 11);
}

void Server::_holdACreateRoomRequest(CommunicatorMessage createDemand)
{
    char *tempRoomName = (char *)createDemand.message.data;
    std::string roomName(11, '\0');

    for (int i = 0; i < 10; i++)
        roomName[i] = tempRoomName[i];
    for (auto it : _activeRoomList) {
        if (it == roomName) {
            _communicatorInstance.get()->sendDataToAClient(createDemand.message.clientInfo, nullptr, 0, 11);
            return;
        }
    }
    unsigned short roomId = createANewRoom(roomName);
    for (auto it : _activeRoomList) {
        if (it == roomId) {
            _communicatorInstance.get()->kickAClient(createDemand.message.clientInfo, it.getNetworkInformations());
            it.startLobbyLoop(); /// WILL BE REMOVED WITH PROCESS IMPLEMENTATION
            return;
        }
    }
}

void Server::_holdANewConnectionRequest(CommunicatorMessage connectionDemand)
{
    /// GET PLAYER NAME AND PASSWORD AND CHECK DATABASE FOR BAN + AUTH PROCESS
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
