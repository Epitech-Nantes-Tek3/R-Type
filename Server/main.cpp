/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** R-Type Main
*/

#include <iostream>
#include "Server.hpp"

using namespace server_data;

int main(int ac, char **av)
{
    if (ac != 3)
        return 84; /// PARSE SERVER ARGUMENT MORE PROPERLY (REBASE MONDAY)
    Server server = Server(std::string(av[1]), std::atoi(av[2]));
    unsigned short roomId = server.createANewRoom();
    std::cerr << "A Room have been created with the id " << roomId << "." << std::endl;
    return 0;
}