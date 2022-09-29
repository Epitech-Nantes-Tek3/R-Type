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

std::vector<Message> Receiver::getMessageList(void) const { return _messageList; }

void Receiver::setMessageList(std::vector<Message> newMessageList) { _messageList = newMessageList; }

Client Receiver::getNetworkData(void) const { return _networkData; }

void Receiver::setNetworkData(Client newNetworkData) { _networkData = newNetworkData; }

void Receiver::addMessage(Message message) { _messageList.push_back(message); }

int Receiver::getMessageListSize(void) const { return _messageList.size(); }

Message Receiver::getLastMessage(void)
{
    _ioService.poll();
    if (_messageList.size() < 1)
        throw std::invalid_argument("No message waiting."); /// TO REFACTO WHEN ERROR CLASS IS IMPLEMENTED
    auto first = _messageList.begin();
    auto temp = *first;
    _messageList.erase(first);
    return temp;
}

Message Receiver::getLastMessageFromClient(Client client)
{
    int pos = 0;

    for (auto i : _messageList) {
        if (i.client_info == client) {
            Message temp = _messageList[pos];
            _messageList.erase(_messageList.begin() + pos);
            return temp;
        }
        pos++;
    }
    throw std::invalid_argument("No message waiting for this client."); /// TO REFACTO WHEN ERROR CLASS IS IMPLEMENTED
}

void Receiver::removeAllClientMessage(Client client)
{
    try {
        getLastMessageFromClient(client);
        removeAllClientMessage(client);
    } catch (std::invalid_argument &e) {
        return;
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
        throw std::invalid_argument("Invalid port and ip address. Please restart the executable.");
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

/// ADD BIND PROTECTIONl