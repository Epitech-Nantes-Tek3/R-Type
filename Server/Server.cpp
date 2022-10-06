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

void Server::createANewRoom(void)
{
    _activeRoomList.push_back(Room());
}

Server::Server()
{
    _activeRoomList = {};
    _networkInformations = Client();
}