/*
** EPITECH PROJECT, 2022
** Project
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
}

unsigned short Server::createANewRoom(void)
{
    _activeRoomList.push_back(Room(_activeRoomList.size(), _networkInformations));
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

Server::Server()
{
    _activeRoomList = {};
    _networkInformations = Client();
}