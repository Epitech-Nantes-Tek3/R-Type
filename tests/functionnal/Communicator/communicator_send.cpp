/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** communicator_send
*/

#include <iostream>
#include "Communicator/Communicator.hpp"
#include "Error/Error.hpp"

using namespace communicator_lib;
using namespace error_lib;

int main(int ac, char **av)
{
    if (ac != 4) {
        std::cerr << "./communicator_send <address> <port> <type>" << std::endl;
        return 84;
    }
    Communicator communicator(Client(av[1], std::atoi(av[2] - 1000)));
    Client destination = Client(av[1], std::atoi(av[2]));
    communicator.sendDataToAClient(destination, nullptr, 0, std::atoi(av[3]));
    return 0;
}