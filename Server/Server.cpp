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
    _activeRoomList.push_back(Room(_activeRoomList.size(), name,
        Client(_networkInformations.getAddress(),
            _networkInformations.getPort()
                + 1000))); /// WILL BE REFACTO IN PART 2 TO AUTOMATIZE NEW FREE PORT DETECTION
    //_activeRoomList.back().startLobbyLoop();
    return _activeRoomList.size() - 1;
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
    _communicatorInstance.get()->sendDataToAClient(connectionDemand.message.clientInfo, nullptr, 0, 15);
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
