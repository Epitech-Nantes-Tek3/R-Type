/*
** EPITECH PROJECT, 2022
** Project
** File description:
** communicator_tests
*/

#include <iostream>
#include "Communicator/Communicator.hpp"

using namespace communicator_lib;

int main(int ac, char **av)
{
    if (ac != 3)
        return 84;
    Communicator communicator(Client(av[1], std::atoi(av[2])));
    communicator.startReceiverListening();
    while (1) {
        try {
            CommunicatorMessage temp = communicator.getLastMessage();
            if (temp.newClient) {
                std::cerr << "Receive a message from a new client ( " << temp.message.clientInfo.getAddress() << " : "
                          << temp.message.clientInfo.getPort() << " ) -> ";
            } else {
                std::cerr << "Receive a message from a current client ( " << temp.message.clientInfo.getAddress()
                          << " : " << temp.message.clientInfo.getPort() << " ) -> ";
            }
            std::cerr << (char *)temp.message.data << std::endl;
        } catch (std::invalid_argument &error) {
        }
    }
    return 0;
}