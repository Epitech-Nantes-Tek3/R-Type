/*
** EPITECH PROJECT, 2022
** Project
** File description:
** Sender
*/

/// @file libs/Communicator/Sender.cpp

#include "Sender.hpp"
#include <boost/asio.hpp>
#include <iostream>

using namespace communicator_lib;
using namespace boost::asio::ip;

Sender::Sender()
{
    _receiverPort = Client().getPort();
}

Sender::Sender(unsigned short receiverPort)
{
    _receiverPort = receiverPort;
}

void Sender::sendDataToAClient(Client &client, void *data, size_t size)
{
    boost::asio::io_service io_service;
    udp::socket socket(io_service);
    udp::endpoint socket_endpoint =
        udp::endpoint(boost::asio::ip::address::from_string(client.getAddress()), client.getPort());
    boost::system::error_code error;
    void *newData = malloc(sizeof(void *) * (size + 2));

    socket.open(udp::v4());
    std::memcpy(newData, &_receiverPort, 2);
    std::memcpy((void *)((char *)newData + sizeof(unsigned short)), data, size);
    auto sent = socket.send_to(boost::asio::buffer(newData, size + 2), socket_endpoint, 0, error);
    std::free(newData);
    socket.close();
    std::cerr << "Message send. " << sent << "bytes transfered." << std::endl;
}

void Sender::sendDataToMultipleClients(std::vector<Client> clients, void *data, size_t size)
{
    for (auto i : clients) {
        sendDataToAClient(i, data, size);
    }
}

Sender::~Sender() {}
