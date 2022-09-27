/*
** EPITECH PROJECT, 2022
** Project
** File description:
** Client
*/

/// \file libs/Communicator/Client.cpp

#include "Client.hpp"
#include <iostream>

using namespace communicator_lib;

Client::Client(std::string address, long port)
{
    this->address = address;
    this->port = port;
    std::cerr << "Creating a client : (" << address << " : " << port << ")." << std::endl;
}

std::string &Client::getAddress(void)
{
    return address;
}

long Client::getPort(void)
{
    return port;
}

void Client::setAddress(std::string address)
{
    this->address = address;
}

void Client::setPort(long port)
{
    this->port = port;
}

Client::~Client()
{
    std::cerr << "Deleting a client : (" << address << " : " << port << ")." << std::endl;
}
