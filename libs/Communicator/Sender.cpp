/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** Sender
*/

/// @file libs/Communicator/Sender.cpp

#include "Sender.hpp"
#include <boost/asio.hpp>
#include <iostream>
#include "Error/Error.hpp"

using namespace communicator_lib;
using namespace boost::asio::ip;

Sender::Sender() { _receiverPort = Client().getPort(); }

Sender::Sender(unsigned short receiverPort) { _receiverPort = receiverPort; }

void Sender::sendDataToAClient(Client &client, void *data, size_t size, unsigned short type)
{
    boost::asio::io_service io_service;
    udp::socket socket(io_service);
    udp::endpoint socket_endpoint =
        udp::endpoint(boost::asio::ip::address::from_string(client.getAddress()), client.getPort());
    boost::system::error_code error;
    void *newData = std::malloc((size + NETWORK_HEADER_SIZE));
    void *dataHeader = generateDataHeader(type);

    if (newData == nullptr)
        throw error_lib::MallocError("Malloc failed.");
    socket.open(udp::v4());
    std::memcpy(newData, dataHeader, NETWORK_HEADER_SIZE);
    std::memcpy((void *)((char *)newData + NETWORK_HEADER_SIZE), data, size);
    socket.send_to(boost::asio::buffer(newData, size + NETWORK_HEADER_SIZE), socket_endpoint, 0, error);
    std::free(newData);
    std::free(dataHeader);
    socket.close();
}

void Sender::sendDataToMultipleClients(std::vector<Client> clients, void *data, size_t size, unsigned short type)
{
    for (auto i : clients) {
        sendDataToAClient(i, data, size, type);
    }
}

void *Sender::generateDataHeader(unsigned short communicationType)
{
    void *dataHeader = std::malloc((NETWORK_HEADER_SIZE));

    if (dataHeader == nullptr)
        throw error_lib::MallocError("Malloc failed.");
    std::memcpy(dataHeader, &_receiverPort, NETWORK_HEADER_SIZE / 2);
    std::memcpy((void *)((char *)dataHeader + NETWORK_HEADER_SIZE / 2), &communicationType, NETWORK_HEADER_SIZE / 2);
    return dataHeader;
}
