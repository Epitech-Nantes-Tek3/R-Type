/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** R-Type Main
*/

#include <iostream>
#include "ArgumentHandler/ArgumentHandler.hpp"
#include "AdminPanel.hpp"

using namespace argument_handler;
using namespace admin_panel;

int main(int ac, char **av)
{
    ArgumentHandler argumentHandler = ArgumentHandler(ac, av);
    ArgumentHandler::ServerInformation serverInformation = argumentHandler.extractServerInformation();
    AdminPanel adminPanel = AdminPanel(serverInformation.address, serverInformation.port);

    adminPanel.startLoop();
    return 0;
}
