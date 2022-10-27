/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** Server
*/

/// @file Server/Server.cpp

#include "Server.hpp"
#include <csignal>
#include "Error/Error.hpp"

using namespace server_data;
using namespace error_lib;
using namespace communicator_lib;

Server::Server(std::string address, unsigned short port) : _communicatorInstance(Communicator(_networkInformations))
{
    _activeRoomList = {};
    _networkInformations = Client(address, port);
}

Server::Server()
{
    _activeRoomList = {};
    _networkInformations = Client();
}

unsigned short Server::createANewRoom(void)
{
    _activeRoomList.push_back(Room(_activeRoomList.size(),
        Client(_networkInformations.getAddress(),
            _networkInformations.getPort()
                + 1000))); /// WILL BE REFACTO IN PART 2 TO AUTOMATIZE NEW FREE PORT DETECTION
    _activeRoomList.back().startLobbyLoop();
    return _activeRoomList.size() - 1;
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
