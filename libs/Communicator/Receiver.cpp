/*
** EPITECH PROJECT, 2022
** R-Type
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
    bindDataTraitmentFunction();
}

Receiver::Receiver(Client networkData)
{
    _messageList = {};
    _networkData = networkData;
    bindDataTraitmentFunction();
}

Message Receiver::getLastMessage(void)
{
    _ioService.poll();
    if (_messageList.size() < 1)
        throw NetworkError("No message waiting for traitment.", "Receiver.cpp -> getLastMessage");
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
        "This client has no message waiting for traitment.", "Receiver.cpp -> getLastMessageFromClient");
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
            "Invalid port and ip address. Please restart the executable.", "Receiver.cpp -> startListening");
    }
    wait();
    _ioService.poll();
}

void Receiver::handleReceive(const boost::system::error_code &error, size_t bytesTransferred)
{
    std::vector<unsigned short> dataHeader;

    if (error) {
        std::cerr << "Receive failed: " << error.message() << std::endl;
        wait();
        return;
    }
    std::cerr << "Receiving data. " << bytesTransferred << "bytes used." << std::endl;
    dataHeader = getDataHeader(_tempData.data());
    std::cerr << "Transfer type : " << dataHeader[1] << std::endl;
    addMessage({Client(_tempRemoteEndpoint.address().to_string(), dataHeader[0]),
        (void *)((char *)_tempData.data() + NETWORK_HEADER_SIZE), bytesTransferred});
    wait();
}

void Receiver::wait(void)
{
    _socket.async_receive_from(boost::asio::buffer(_tempData), _tempRemoteEndpoint,
        boost::bind(&Receiver::handleReceive, this, boost::asio::placeholders::error,
            boost::asio::placeholders::bytes_transferred));
}

std::vector<unsigned short> Receiver::getDataHeader(void *data)
{
    unsigned short receiverPort = 0;
    unsigned short communicationType = 0;

    std::memcpy(&receiverPort, data, NETWORK_HEADER_SIZE / 2);
    std::memcpy(&communicationType, (void *)((char *)data + NETWORK_HEADER_SIZE / 2), NETWORK_HEADER_SIZE / 2);
    return std::vector<unsigned short>{receiverPort, communicationType};
}

void Receiver::dataTraitmentType10(Message dataContent)
{
    (void) dataContent;
}

void Receiver::dataTraitmentType20(Message dataContent)
{
    (void) dataContent;
}

void Receiver::dataTraitmentType21(Message dataContent)
{
    (void) dataContent;
}

void Receiver::dataTraitmentType30(Message dataContent)
{
    (void) dataContent;
}

void Receiver::bindDataTraitmentFunction(void)
{
    _dataTraitment[10] = std::bind(&Receiver::dataTraitmentType10, this, std::placeholders::_1);
    _dataTraitment[20] = std::bind(&Receiver::dataTraitmentType20, this, std::placeholders::_1);
    _dataTraitment[21] = std::bind(&Receiver::dataTraitmentType21, this, std::placeholders::_1);
    _dataTraitment[30] = std::bind(&Receiver::dataTraitmentType30, this, std::placeholders::_1);
}

Receiver::~Receiver() {}
