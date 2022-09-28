/*
** EPITECH PROJECT, 2022
** Project
** File description:
** Receiver_tests
*/

#include <criterion/criterion.h>
#include "Communicator/Receiver.hpp"

using namespace communicator_lib;

Test(receiver_testing, basic_init)
{
    Receiver receiver = Receiver();
    Receiver receiver_two = Receiver(Client("190.1.1.1", 10));

    cr_assert_eq(receiver.getNetworkData().getPort(), 0);
    cr_assert_eq(receiver_two.getNetworkData().getPort(), 10);
}