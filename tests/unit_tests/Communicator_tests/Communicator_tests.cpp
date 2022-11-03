/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** Communicator_tests
*/

#include <criterion/criterion.h>
#include "Communicator/Communicator.hpp"
#include "Error/Error.hpp"

using namespace communicator_lib;
using namespace error_lib;

Test(communicator_testing, basic_init)
{
    Communicator communicator = Communicator();

    cr_assert_eq(communicator.getClientList().size(), 0);
}

Test(communicator_testing, add_client)
{
    Communicator communicator = Communicator();
    Client client = Client();

    communicator.addClientToList(client);
    cr_assert_eq(communicator.getClientList().size(), 1);
}

Test(communicator_testing, add_client_multiple)
{
    Communicator communicator = Communicator();
    Client client = Client();
    Client client_two = Client("190.1.1.1", 10);

    communicator.addClientToList(client);
    cr_assert_eq(communicator.getClientList().size(), 1);
    try {
        communicator.addClientToList(client);
        cr_assert_eq(41, 42);
    } catch (NetworkError &e) {
        cr_assert_eq(42, 42);
    }
    cr_assert_eq(communicator.getClientList().size(), 1);
    communicator.addClientToList(client_two);
    cr_assert_eq(communicator.getClientList().size(), 2);
}

Test(communicator_testing, remove_client)
{
    Communicator communicator = Communicator();
    Client client = Client();
    Client client_two = Client("190.1.1.1", 10);

    communicator.addClientToList(client);
    communicator.addClientToList(client_two);
    communicator.removeClientFromList(client);
    cr_assert_eq(communicator.getClientList().size(), 1);
    communicator.removeClientFromList(client);
    cr_assert_eq(communicator.getClientList().size(), 1);
    communicator.removeClientFromList(client_two);
    cr_assert_eq(communicator.getClientList().size(), 0);
}

Test(communicator_testing, get_client)
{
    Communicator communicator = Communicator();
    Client client = Client();
    Client client_two = Client("190.1.1.1", 10);

    communicator.addClientToList(client);
    communicator.addClientToList(client_two);
    cr_assert_eq(communicator.getClientFromList("190.1.1.1", 10) == client_two, true);
    cr_assert_eq(communicator.getClientFromList("127.0.0.1", 0) == client, true);
    try {
        communicator.getClientFromList("99999", 0);
        cr_assert_eq(1, 2);
    } catch (NetworkError &e) {
        cr_assert_eq(1, 1);
    }
}

Test(communicator_testing, chat_message_operation)
{
    Communicator communicator = Communicator();
    Client client = Client();
    std::string pseudo = "Lucas";
    std::string messageContent = "Je suis lucas !";

    communicator.addClientToList(client);
    communicator.utilitarySendChatMessage(pseudo, messageContent, {0});
    void *networkObject = std::malloc(sizeof(char) * (pseudo.size() + messageContent.size()) + sizeof(unsigned short));
    unsigned short pseudoLen = pseudo.size();

    if (networkObject == nullptr)
        throw MallocError("Malloc failed.");
    std::memcpy(networkObject, &pseudoLen, sizeof(unsigned short));
    std::memcpy((void *)((char *)networkObject + sizeof(unsigned short)), pseudo.c_str(), sizeof(char) * pseudoLen);
    std::memcpy((void *)((char *)networkObject + sizeof(unsigned short) + sizeof(char) * pseudoLen),
        messageContent.c_str(), sizeof(char) * messageContent.size());
    size_t messageSize = sizeof(unsigned short) + sizeof(char) * (pseudo.size() + messageContent.size());
    CommunicatorMessage cryptedData = {{client, networkObject, messageSize, 50}, true};
    std::vector<std::string> uncryptedData = communicator.utilitaryReceiveChatMessage(cryptedData);

    cr_assert_eq(uncryptedData.at(0), pseudo);
    cr_assert_eq(uncryptedData.at(1), messageContent);
}