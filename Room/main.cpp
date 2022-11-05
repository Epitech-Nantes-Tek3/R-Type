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
    std::cerr << "HEY POTO" << std::endl;
    ArgumentHandler argumentHandler = ArgumentHandler(ac, av);
    ArgumentHandler::RoomInformation roomInformations = argumentHandler.extractRoomInformations();

    std::cerr << "???" << std::endl;
    server_data::Room room(
        roomInformations.id, roomInformations.name, Client(roomInformations.address, roomInformations.port));
    std::cerr << "L" << std::endl;
    room.startLobbyLoop();
    return 0;
}
