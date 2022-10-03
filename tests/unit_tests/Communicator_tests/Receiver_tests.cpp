/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** Receiver_tests
*/

#include <criterion/criterion.h>
#include "Communicator/Receiver.hpp"
#include "Error/Error.hpp"

using namespace communicator_lib;
using namespace error_lib;

Test(receiver_testing, basic_init)
{
    Receiver receiver = Receiver();
    Receiver receiver_two = Receiver(Client("190.1.1.1", 10));

    cr_assert_eq(receiver.getNetworkData().getPort(), 0);
    cr_assert_eq(receiver_two.getNetworkData().getPort(), 10);
}

Test(receiver_testing, set_init)
{
    Receiver receiver = Receiver();

    receiver.setNetworkData(Client("190.1.1.1", 10));
    cr_assert_eq(receiver.getNetworkData().getPort(), 10);
}

Test(receiver_testing, add_message)
{
    Receiver receiver = Receiver();
    Message message = {Client(), nullptr, 0, 0};

    receiver.addMessage(message);
    cr_assert_eq(receiver.getMessageListSize(), 1);
}

Test(receiver_testing, get_last_message)
{
    Receiver receiver = Receiver();
    Message message = {Client(), nullptr, 0, 0};
    Message message_two = {Client(), nullptr, 1, 0};

    try {
        receiver.getLastMessage();
        cr_assert_eq(42, 41);
    } catch (NetworkError &e) {
        cr_assert_eq(42, 42);
    }
    receiver.addMessage(message);
    try {
        auto temp = receiver.getLastMessage();
        cr_assert_eq(temp.size, 0);
    } catch (NetworkError &e) {
        cr_assert_eq(41, 42);
    }
    cr_assert_eq(receiver.getMessageListSize(), 0);
    receiver.addMessage(message);
    receiver.addMessage(message_two);
    cr_assert_eq(receiver.getMessageListSize(), 2);
    try {
        auto temp = receiver.getLastMessage();
        cr_assert_eq(temp.size, 0);
        cr_assert_eq(receiver.getMessageListSize(), 1);
        temp = receiver.getLastMessage();
        cr_assert_eq(temp.size, 1);
        cr_assert_eq(receiver.getMessageListSize(), 0);
    } catch (NetworkError &e) {
        cr_assert_eq(41, 42);
    }
}

Test(receiver_testing, get_last_message_from_client)
{
    Receiver receiver = Receiver();
    Message message = {Client(), nullptr, 0, 0};
    Message message_two = {Client(), nullptr, 1, 0};
    Message message_three = {Client("100.1.1.1", 10), nullptr, 2, 0};

    receiver.addMessage(message);
    receiver.addMessage(message_three);
    receiver.addMessage(message_two);
    cr_assert_eq(receiver.getMessageListSize(), 3);
    try {
        auto temp = receiver.getLastMessageFromClient(Client());
        cr_assert_eq(temp.size, 0);
        cr_assert_eq(receiver.getMessageListSize(), 2);
        temp = receiver.getLastMessageFromClient(Client());
        cr_assert_eq(temp.size, 1);
        cr_assert_eq(receiver.getMessageListSize(), 1);
    } catch (NetworkError &e) {
        cr_assert_eq(41, 42);
    }
}

Test(receiver_testing, remove_all_client_message)
{
    Receiver receiver = Receiver();
    Message message = {Client(), nullptr, 0, 0};
    Message message_two = {Client(), nullptr, 1, 0};
    Message message_three = {Client("100.1.1.1", 10), nullptr, 2, 0};

    receiver.addMessage(message);
    receiver.addMessage(message_three);
    receiver.addMessage(message_two);
    cr_assert_eq(receiver.getMessageListSize(), 3);
    receiver.removeAllClientMessage(Client());
    cr_assert_eq(receiver.getMessageListSize(), 1);
    receiver.removeAllClientMessage(Client("100.1.1.1", 10));
    cr_assert_eq(receiver.getMessageListSize(), 0);
}