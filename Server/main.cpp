/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** R-Type Main
*/

#include <iostream>
#include "ArgumentHandler/ArgumentHandler.hpp"
#include "Server.hpp"

using namespace server_data;
using namespace argument_handler;

int main(int ac, char **av)
{
    ArgumentHandler argumentHandler = ArgumentHandler(ac, av);
    ArgumentHandler::ServerInformation serverInformation;
    try {
        serverInformation = argumentHandler.extractServerInformation();
    } catch (std::exception &exc) {
        std::cerr << exc.what() << std::endl;
        return 84;
    }
    Server server = Server(serverInformation.address, serverInformation.port);

    server.startHubLoop();
    return 0;
}
