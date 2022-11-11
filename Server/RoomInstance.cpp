/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** RoomInstance
*/

#include "Error/Error.hpp"
#include "Server.hpp"

namespace server_data
{
    RoomInstance::RoomInstance(
        Server *server, unsigned short id, std::string name, std::string address, unsigned short port, std::string playerNumber)
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
        _terminated = false;
        _input = new boost::process::opstream();
        _output = new boost::process::ipstream();
        try {
            std::string executableName = "r-type_room";
#ifdef _WIN32
            executableName.append(".exe");
#endif

            _child = new boost::process::child(executableName, std::to_string(_id), _name,
                _networkInformations.getAddress(), std::to_string(_networkInformations.getPort()), playerNumber,
                boost::process::std_in<(*_input), boost::process::std_out>(*_output));
        } catch (const std::system_error &error) {
            std::cerr << "ERROR while launching a new room: " << std::to_string(error.code().value()) << " : "
                      << error.what() << std::endl;
        }
        _inputHandler = std::make_unique<boost::thread>(&RoomInstance::_manageInterprocessCommunication, this, server);
    }

    void RoomInstance::_manageInterprocessCommunication(Server *server)
    {
        std::string line;

        while (!_terminated && _output && std::getline((*_output), line) && !line.empty()) {
            _manageStatusResponse(line);
            _manageSeatsResponse(line);
            _manageStopResponse(line, server);
            _manageEndGameRoom(line);
        }
    }

    void RoomInstance::_manageStatusResponse(std::string line)
    {
        if (line.compare(0, 3, "21 ") == 0 && !(line.erase(0, 3).empty())) {
            _state = RoomState(std::stoi(line));
        }
    }

    void RoomInstance::_manageSeatsResponse(std::string line)
    {
        if (line.compare(0, 3, "22 ") == 0 && !(line.erase(0, 3).empty())) {
            _remainingPlaces = std::stoi(line);
        }
    }

    void RoomInstance::_manageStopResponse(std::string line, Server *server)
    {
        if (line == "23") {
            _terminated = true;
            server->deleteARoom(_id);
        }
    }

    void RoomInstance::_manageEndGameRoom(std::string line)
    {
        if (line == "24") {
            _stop();
        }
    }

    void RoomInstance::_stop() { (*_input) << "13" << std::endl; }

    RoomInstance::~RoomInstance()
    {
        if (!_terminated) {
            _stop();
            _terminated = true;
        }
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
        if (boost::this_thread::get_id() != _inputHandler->get_id())
            _inputHandler->join();
    }
} // namespace server_data
