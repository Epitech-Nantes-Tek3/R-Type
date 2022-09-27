/*
** EPITECH PROJECT, 2022
** Project
** File description:
** Client_tests
*/

#include <criterion/criterion.h>
#include "Communicator/Client.hpp"

using namespace communicator_lib;

Test(client_testing, basic_init)
{
    Client client = Client("198.0.0.1", 10);

    cr_assert_eq(client.getAddress(), "198.0.0.1");
    cr_assert_eq(client.getPort(), 10);
}

Test(client_testing, default_init)
{
    Client client = Client();

    cr_assert_eq(client.getAddress(), "127.0.0.1");
    cr_assert_eq(client.getPort(), 0);
}

Test(client_testing, setter)
{
    Client client = Client();

    client.setAddress("198.0.0.1");
    client.setPort(10);
    cr_assert_eq(client.getAddress(), "198.0.0.1");
    cr_assert_eq(client.getPort(), 10);
}