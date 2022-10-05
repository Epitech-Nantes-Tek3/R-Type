/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** communicator_switch
*/

#include <iostream>
#include "Communicator/Communicator.hpp"
#include "Error/Error.hpp"

using namespace communicator_lib;
using namespace error_lib;

int main(int ac, char **av)
{
    if (ac != 3)
        return 84;
    Communicator communicator_one(Client(av[1], std::atoi(av[2])));
    Communicator communicator_two(Client(av[1], std::atoi(av[2]) + 1000));
    Communicator communicator_three(Client(av[1], std::atoi(av[2]) + 2000));
    Client sendingClient = Client(av[1], std::atoi(av[2]));
    char *sendingSentence = (char *)"First connection.";

    communicator_one.startReceiverListening();
    communicator_two.startReceiverListening();
    communicator_three.startReceiverListening();
    communicator_three.sendDataToAClient(
        sendingClient, sendingSentence, std::strlen(sendingSentence) * sizeof(char), 10);
    while (1) {
        try {
            CommunicatorMessage temp = communicator_one.getLastMessage();
            std::cerr << "Receive a message from a new client ( " << temp.message.clientInfo.getAddress() << " : "
                      << temp.message.clientInfo.getPort() << " ) -> ";
            std::cerr << "Receive a message -> " << (char *)temp.message.data << std::endl;
            communicator_one.kickAClient(
                Client(av[1], std::atoi(av[2]) + 2000), Client(av[1], std::atoi(av[2]) + 1000));
        } catch (NetworkError &error) {
        }
        try {
            CommunicatorMessage temp = communicator_two.getLastMessage();
        } catch (NetworkError &error) {
        }
        try {
            CommunicatorMessage temp = communicator_three.getLastMessage();
        } catch (NetworkError &error) {
        }
    }
}