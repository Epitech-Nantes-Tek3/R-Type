/*
** EPITECH PROJECT, 2022
** Project
** File description:
** Receiver
*/

/// @file libs/Communicator/Receiver.cpp

#include "Receiver.hpp"
#include <boost/bind/bind.hpp>
#include <iostream>
#include "Error/Error.hpp"

using namespace communicator_lib;
using namespace error_lib;
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

Message Receiver::getLastMessage(void)
{
    _ioService.poll();
    if (_messageList.size() < 1)
        throw NetworkError("No message waiting for traitment.", "Receiver.cpp:33 -> getLastMessage");
    auto first = _messageList.begin();
    auto temp = *first;
    _messageList.erase(first);
    return temp;
}

Message Receiver::getLastMessageFromClient(Client client)
{
    int pos = 0;

    for (auto i : _messageList) {
        if (i.clientInfo == client) {
            Message temp = _messageList[pos];
            _messageList.erase(_messageList.begin() + pos);
            return temp;
        }
        pos++;
    }
    throw NetworkError(
        "This client has no message waiting for traitment.", "Receiver.cpp:53 -> getLastMessageFromClient");
}

void Receiver::removeAllClientMessage(Client client)
{
    try {
        getLastMessageFromClient(client);
        removeAllClientMessage(client);
    } catch (NetworkError &e) {
    }
}

void Receiver::startListening(void)
{
    _socket.open(boost::asio::ip::udp::v4());
    try {
        _socket.bind(boost::asio::ip::udp::endpoint(
            boost::asio::ip::address::from_string(_networkData.getAddress()), _networkData.getPort()));
    } catch (boost::system::system_error &error) {
        std::cerr << "Bind failed. " << error.what() << std::endl;
        throw NetworkError(
            "Invalid port and ip address. Please restart the executable.", "Receiver.cpp:74 -> startListening");
    }
    wait();
    _ioService.poll();
}

void Receiver::handleReceive(const boost::system::error_code &error, size_t bytesTransferred)
{
    unsigned short temporaryPort = 0;

    if (error) {
        std::cerr << "Receive failed: " << error.message() << std::endl;
        wait();
        return;
    }
    std::cerr << "Receiving data. " << bytesTransferred << "bytes used." << std::endl;
    std::memcpy(&temporaryPort, _tempData.data(), 2);
    addMessage({Client(_tempRemoteEndpoint.address().to_string(), temporaryPort),
        (void *)((char *)_tempData.data() + sizeof(unsigned short)), bytesTransferred});
    wait();
}

void Receiver::wait(void)
{
    _socket.async_receive_from(boost::asio::buffer(_tempData), _tempRemoteEndpoint,
        boost::bind(&Receiver::handleReceive, this, boost::asio::placeholders::error,
            boost::asio::placeholders::bytes_transferred));
}

Receiver::~Receiver() {}
