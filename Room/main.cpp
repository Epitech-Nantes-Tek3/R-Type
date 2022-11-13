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
    ArgumentHandler::RoomInformation roomInformations;
    try {
        roomInformations = argumentHandler.extractRoomInformations();
    } catch (std::exception &exc) {
        std::cerr << exc.what() << std::endl;
        return 84;
    }
    server_data::Room room(roomInformations.id, roomInformations.name,
        Client(roomInformations.address, roomInformations.port), roomInformations.configs);
    room.startLobbyLoop();
    return 0;
}
