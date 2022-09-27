/*
** EPITECH PROJECT, 2022
** Project
** File description:
** Client
*/

#include "Client.hpp"
#include <iostream>

using namespace communicator_lib;

Client::Client(std::string address, long port)
{
    this->address = address;
    this->port = port;
    std::cerr << "Creating a client : (" << address << " : " << port << ")." << std::endl;
}

Client::~Client()
{
    std::cerr << "Deleting a client : (" << address << " : " << port << ")." << std::endl;
}
