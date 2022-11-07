/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** R-Type Main
*/

#include <iostream>
#include "AdminPanel.hpp"
#include "ArgumentHandler/ArgumentHandler.hpp"

using namespace argument_handler;
using namespace admin_panel;

int main(int ac, char **av)
{
    ArgumentHandler argumentHandler = ArgumentHandler(ac, av);
    ArgumentHandler::ClientInformation clientInformation = argumentHandler.extractClientInformation();
    AdminPanel adminPanel = AdminPanel(clientInformation.clientAddress, clientInformation.clientPort,
        clientInformation.serverAddress, clientInformation.serverPort);

    adminPanel.startLoop();
    return 0;
}
