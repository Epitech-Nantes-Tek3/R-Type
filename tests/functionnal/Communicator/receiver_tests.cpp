/*
** EPITECH PROJECT, 2022
** Project
** File description:
** receiver_tests
*/

#include <iostream>
#include "Communicator/Receiver.hpp"

using namespace communicator_lib;

int main(int ac, char **av)
{
    Client client;

    if (ac != 3)
        return -1;
    client = Client(av[1], std::atoi(av[2]));
    Receiver receiver = Receiver(client);
    receiver.startListening();
    while (1) {
        try {
            Message temp = receiver.getLastMessage();
            std::cerr << "Message from " << temp.client_info.getAddress() << " -> " << temp.client_info.getPort()
                      << " of size : " << temp.size << std::endl;
            std::cerr << "Remaining message : " << receiver.getMessageListSize() << std::endl;
        } catch (std::invalid_argument &error) {
        }
    }
    return 0;
}