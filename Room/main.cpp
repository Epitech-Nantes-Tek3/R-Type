/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** R-Type Main
*/

#include <iostream>
#include "ArgumentHandler/ArgumentHandler.hpp"
#include "Room.hpp"

using namespace argument_handler;

int main(int ac, char **av)
{
    ArgumentHandler argumentHandler = ArgumentHandler(ac, av);
    ArgumentHandler::RoomInformation roomInformations = argumentHandler.extractRoomInformations();

    serverData::Room room(
        roomInformations.id, roomInformations.name, Client(roomInformations.address, roomInformations.port));
    room.startLobbyLoop();
    return 0;
}
