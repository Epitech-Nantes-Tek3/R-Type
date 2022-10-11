/*
** EPITECH PROJECT, 2022
** R-Type
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
    _id = 0;
}

