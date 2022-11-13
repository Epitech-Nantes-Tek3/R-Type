/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** R-Type Main
*/

#include <iostream>
#include "ArgumentHandler/ArgumentHandler.hpp"
#include "Error/Error.hpp"
#include "Room.hpp"

using namespace error_lib;
using namespace argument_handler;

int main(int ac, char **av)
{
    ArgumentHandler argumentHandler = ArgumentHandler(ac, av);
    ArgumentHandler::RoomInformation roomInformations;
    roomInformations = argumentHandler.extractRoomInformations();
    server_data::Room room(roomInformations.id, roomInformations.name,
        Client(roomInformations.address, roomInformations.port), roomInformations.configs);
    room.startLobbyLoop();
    return 0;
}
