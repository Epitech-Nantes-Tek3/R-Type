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
    throw NetworkError("This client has no message waiting for traitment.", "Receiver.cpp -> getLastMessageFromClient");
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
    void *temp = std::malloc(bytesTransferred);

    if (temp == nullptr)
        throw std::logic_error("Malloc failed.");
    std::memcpy(temp, _tempData.data(), bytesTransferred);
    if (error) {
        std::cerr << "Receive failed: " << error.message() << std::endl;
        wait();
        return;
    }
    dataHeader = getDataHeader(temp);
    if (_dataTraitment.find(dataHeader[1]) == _dataTraitment.end())
        return;
    _dataTraitment[dataHeader[1]](
        {Client(_tempRemoteEndpoint.address().to_string(), dataHeader[0]), temp, bytesTransferred, 0});
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
    addMessage({dataContent.clientInfo, (void *)((char *)dataContent.data + NETWORK_HEADER_SIZE),
        dataContent.size - NETWORK_HEADER_SIZE, 10});
}

void Receiver::dataTraitmentType11(Message dataContent)
{
    addMessage({dataContent.clientInfo, (void *)((char *)dataContent.data + NETWORK_HEADER_SIZE),
        dataContent.size - NETWORK_HEADER_SIZE, 11});
}

void Receiver::dataTraitmentType12(Message dataContent)
{
    addMessage({dataContent.clientInfo, (void *)((char *)dataContent.data + NETWORK_HEADER_SIZE),
        dataContent.size - NETWORK_HEADER_SIZE, 12});
}

void Receiver::dataTraitmentType13(Message dataContent)
{
    addMessage({dataContent.clientInfo, (void *)((char *)dataContent.data + NETWORK_HEADER_SIZE),
        dataContent.size - NETWORK_HEADER_SIZE, 13});
}

void Receiver::dataTraitmentType14(Message dataContent)
{
    addMessage({dataContent.clientInfo, (void *)((char *)dataContent.data + NETWORK_HEADER_SIZE),
        dataContent.size - NETWORK_HEADER_SIZE, 14});
}

void Receiver::dataTraitmentType15(Message dataContent)
{
    addMessage({dataContent.clientInfo, (void *)((char *)dataContent.data + NETWORK_HEADER_SIZE),
        dataContent.size - NETWORK_HEADER_SIZE, 15});
}

void Receiver::dataTraitmentType16(Message dataContent)
{
    addMessage({dataContent.clientInfo, (void *)((char *)dataContent.data + NETWORK_HEADER_SIZE),
        dataContent.size - NETWORK_HEADER_SIZE, 16});
}

void Receiver::dataTraitmentType17(Message dataContent)
{
    addMessage({dataContent.clientInfo, (void *)((char *)dataContent.data + NETWORK_HEADER_SIZE),
        dataContent.size - NETWORK_HEADER_SIZE, 17});
}

void Receiver::dataTraitmentType20(Message dataContent)
{
    unsigned short endpointPort = 0;
    char *endpointAddress = nullptr;
    Client newEndpoint = Client();
    void *data = (void *)((char *)dataContent.data + NETWORK_HEADER_SIZE);

    std::memcpy(&endpointPort, data, sizeof(unsigned short));
    endpointAddress = (char *)data + sizeof(unsigned short);
    newEndpoint.setAddress(std::string(endpointAddress));
    newEndpoint.setPort(endpointPort);
    addMessage({newEndpoint, nullptr, 0, 20});
    addMessage({dataContent.clientInfo, nullptr, 0, 20});
}

void Receiver::dataTraitmentType21(Message dataContent) { addMessage({dataContent.clientInfo, nullptr, 0, 21}); }

void Receiver::dataTraitmentType30(Message dataContent)
{
    addMessage({dataContent.clientInfo, (void *)((char *)dataContent.data + NETWORK_HEADER_SIZE),
        dataContent.size - NETWORK_HEADER_SIZE, 30});
}

void Receiver::dataTraitmentType31(Message dataContent)
{
    addMessage({dataContent.clientInfo, (void *)((char *)dataContent.data + NETWORK_HEADER_SIZE),
        dataContent.size - NETWORK_HEADER_SIZE, 31});
}

void Receiver::dataTraitmentType40(Message dataContent)
{
    addMessage({dataContent.clientInfo, (void *)((char *)dataContent.data + NETWORK_HEADER_SIZE),
        dataContent.size - NETWORK_HEADER_SIZE, 40});
}

void Receiver::dataTraitmentType41(Message dataContent)
{
    addMessage({dataContent.clientInfo, (void *)((char *)dataContent.data + NETWORK_HEADER_SIZE),
        dataContent.size - NETWORK_HEADER_SIZE, 41});
}

void Receiver::dataTraitmentType42(Message dataContent)
{
    addMessage({dataContent.clientInfo, (void *)((char *)dataContent.data + NETWORK_HEADER_SIZE),
        dataContent.size - NETWORK_HEADER_SIZE, 42});
}

void Receiver::dataTraitmentType43(Message dataContent)
{
    addMessage({dataContent.clientInfo, (void *)((char *)dataContent.data + NETWORK_HEADER_SIZE),
        dataContent.size - NETWORK_HEADER_SIZE, 43});
}

void Receiver::dataTraitmentType50(Message dataContent)
{
    addMessage({dataContent.clientInfo, (void *)((char *)dataContent.data + NETWORK_HEADER_SIZE),
        dataContent.size - NETWORK_HEADER_SIZE, 50});
}

void Receiver::bindDataTraitmentFunction(void)
{
    _dataTraitment[10] = std::bind(&Receiver::dataTraitmentType10, this, std::placeholders::_1);
    _dataTraitment[11] = std::bind(&Receiver::dataTraitmentType11, this, std::placeholders::_1);
    _dataTraitment[12] = std::bind(&Receiver::dataTraitmentType12, this, std::placeholders::_1);
    _dataTraitment[13] = std::bind(&Receiver::dataTraitmentType13, this, std::placeholders::_1);
    _dataTraitment[14] = std::bind(&Receiver::dataTraitmentType14, this, std::placeholders::_1);
    _dataTraitment[15] = std::bind(&Receiver::dataTraitmentType15, this, std::placeholders::_1);
    _dataTraitment[16] = std::bind(&Receiver::dataTraitmentType16, this, std::placeholders::_1);
    _dataTraitment[17] = std::bind(&Receiver::dataTraitmentType17, this, std::placeholders::_1);
    _dataTraitment[20] = std::bind(&Receiver::dataTraitmentType20, this, std::placeholders::_1);
    _dataTraitment[21] = std::bind(&Receiver::dataTraitmentType21, this, std::placeholders::_1);
    _dataTraitment[30] = std::bind(&Receiver::dataTraitmentType30, this, std::placeholders::_1);
    _dataTraitment[31] = std::bind(&Receiver::dataTraitmentType31, this, std::placeholders::_1);
    _dataTraitment[40] = std::bind(&Receiver::dataTraitmentType40, this, std::placeholders::_1);
    _dataTraitment[41] = std::bind(&Receiver::dataTraitmentType41, this, std::placeholders::_1);
    _dataTraitment[42] = std::bind(&Receiver::dataTraitmentType42, this, std::placeholders::_1);
    _dataTraitment[43] = std::bind(&Receiver::dataTraitmentType43, this, std::placeholders::_1);
    _dataTraitment[50] = std::bind(&Receiver::dataTraitmentType50, this, std::placeholders::_1);
}

Receiver::~Receiver() {}
