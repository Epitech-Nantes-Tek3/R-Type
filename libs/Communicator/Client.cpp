/*
** EPITECH PROJECT, 2022
** Project
** File description:
** Client
*/

/// @file libs/Communicator/Client.cpp

#include "Client.hpp"
#include <iostream>

using namespace communicator_lib;

Client::Client(std::string address, long port)
{
    this->_address = address;
    this->_port = port;
    std::cerr << "Creating a client : (" << _address << " : " << _port << ")." << std::endl;
}

std::string Client::getAddress(void) const { return _address; }

long Client::getPort(void) const { return _port; }

void Client::setAddress(std::string address) { this->_address = address; }

void Client::setPort(long port) { this->_port = port; }

Client::~Client() { std::cerr << "Deleting a client : (" << _address << " : " << _port << ")." << std::endl; }
