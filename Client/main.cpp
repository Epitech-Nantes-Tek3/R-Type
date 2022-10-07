/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** main for the client
*/

#include <SFML/Graphics.hpp>
#include "ClientRoom.hpp"

using namespace client_data;

int main(int ac, char **av)
{
    if (ac != 5)
        return 84; /// PARSE CLIENT ARGUMENT MORE PROPERLY (REBASE MONDAY)
    ClientRoom client = ClientRoom(std::string(av[1]), std::atoi(av[2]), std::string(av[3]), std::atoi(av[4]));
    client.startLobbyLoop();
    return (0);
}
