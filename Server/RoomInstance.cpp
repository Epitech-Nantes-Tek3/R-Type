/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** RoomInstance
*/

#include "RoomInstance.hpp"
#include "Error/Error.hpp"

#include <iostream>

namespace serverData
{
    RoomInstance::RoomInstance(unsigned short id, std::string name, std::string address, unsigned short port)
    {
        _id = id;
        if (name == "")
            throw error_lib::RoomError("Try to create a room with a null name.", "RoomInstance.cpp -> RoomInstance");
        _name = name;
        if (address == "")
            throw error_lib::RoomError("Try to create a room with a null address.", "RoomInstance.cpp -> RoomInstance");
        if (port == 0)
            throw error_lib::RoomError("Try to create a room with a null port.", "RoomInstance.cpp -> RoomInstance");
        _networkInformations = communicator_lib::Client(address, port);
        _input = new boost::process::opstream();
        _output = new boost::process::ipstream();
        _child = new boost::process::child("r-type_room", std::to_string(_id), _name, _networkInformations.getAddress(),
            std::to_string(_networkInformations.getPort()),
            boost::process::std_in<(*_input), boost::process::std_out>(*_output));
    }

    RoomInstance::~RoomInstance()
    {
        if (_child) {
            if (_child->running()) {
                terminate();
                wait();
            }
            delete _child;
        }
        if (_input)
            delete _input;
        if (_output)
            delete _output;
    }
} // namespace serverData
