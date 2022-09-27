/*
** EPITECH PROJECT, 2022
** Project
** File description:
** Communicator_tests
*/

#include <criterion/criterion.h>
#include "Communicator/Communicator.hpp"

using namespace communicator_lib;

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
    communicator.addClientToList(client);
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
    } catch (std::invalid_argument &e) {
        cr_assert_eq(1, 1);
    }
}
