/*
** EPITECH PROJECT, 2022
** Project
** File description:
** Receiver
*/

/// @file libs/Communicator/Receiver.cpp

#include "Receiver.hpp"
#include <boost/asio.hpp>
#include <boost/array.hpp>
#include <boost/bind/bind.hpp>
#include <iostream>

using namespace communicator_lib;
using namespace boost::asio::ip;

Receiver::Receiver()
{
    _messageList = {};
    _networkData = Client();
}

Receiver::Receiver(Client networkData)
{
    _messageList = {};
    _networkData = networkData;
}

std::vector<Message> Receiver::getMessageList(void) const
{
    return _messageList;
}

void Receiver::setMessageList(std::vector<Message> newMessageList)
{
    _messageList = newMessageList;
}

Message &Receiver::getLastMessage(void)
{
    return _messageList[0]; /// TO UPDATE
}

Message &Receiver::getLastMessageFromClient(Client client)
{
    (void) client;
    return _messageList[0]; /// TO UPDATE
}

void Receiver::removeAClientMessage(Client client)
{
    (void) client; /// TO UPDATE
}

void Receiver::removeAllClientMessage(Client client)
{
    (void) client; /// TO UPDATE
}

Receiver::~Receiver()
{
}
