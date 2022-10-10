/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** R-Type Main
*/

#include <iostream>
#include "ArgumentHandler.hpp"
#include "Server.hpp"

using namespace server_data;

int main(int ac, char **av)
{
    ArgumentHandler argumentHandler = ArgumentHandler(ac, av);
    ArgumentHandler::ServerInformation serverInformation = argumentHandler.extractServerInformation();
    Server server = Server(serverInformation.address, serverInformation.port);
    unsigned short roomId = server.createANewRoom();

    std::cerr << "A Room have been created with the id " << roomId << "." << std::endl;
    return 0;
}
