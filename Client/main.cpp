/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** main for the client
*/

#include "ArgumentHandler/ArgumentHandler.hpp"
#include "ClientRoom.hpp"
#include "Error/Error.hpp"
#include "UserConnection.hpp"

using namespace client_data;
using namespace argument_handler;
using namespace error_lib;

int main(int ac, char **av)
{
    try {
        ArgumentHandler argumentHandler = ArgumentHandler(ac, av);
        ArgumentHandler::ClientInformation clientInformation = argumentHandler.extractClientInformation();
        ClientRoom client = ClientRoom(clientInformation.clientAddress, clientInformation.clientPort,
            clientInformation.serverAddress, clientInformation.serverPort);

        if (client.startGame() == 84)
            return 84;
    } catch (RTypeError &e) {
        std::cerr << e.what() << " from " << e.getComponent() << std::endl;
    }
    return (0);
}
