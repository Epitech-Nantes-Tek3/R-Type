/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** R-Type Main
*/

#include <iostream>
#include "ArgumentHandler/ArgumentHandler.hpp"
#include "Error/Error.hpp"
#include "Server.hpp"

using namespace server_data;
using namespace argument_handler;
using namespace error_lib;

int main(int ac, char **av)
{
    try {
        ArgumentHandler argumentHandler = ArgumentHandler(ac, av);
        ArgumentHandler::ServerInformation serverInformation = argumentHandler.extractServerInformation();
        Server server = Server(serverInformation.address, serverInformation.port);

        server.startHubLoop();
    } catch (RTypeError &e) {
        std::cerr << e.what() << " from " << e.getComponent() << std::endl;
    }
    return 0;
}
