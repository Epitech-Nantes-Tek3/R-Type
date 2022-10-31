/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** ArgumentHandler
*/

/// @file libs/ArgumentHandler.hpp

#include "ArgumentHandler.hpp"
#include <boost/algorithm/string.hpp>
#include <iostream>
#include "Error/Error.hpp"

using namespace argument_handler;
using namespace error_lib;

ArgumentHandler::ArgumentHandler()
{
    _argumentsToParse = {};
    bindAllHOptionText();
}

ArgumentHandler::ArgumentHandler(const int ac, char **av)
{
    _argumentsToParse = {};
    for (int i = 1; i < ac; i++) {
        _argumentsToParse.push_back(std::string(av[i]));
    }
    bindAllHOptionText();
}

void ArgumentHandler::bindAllHOptionText(void)
{
    _hTextList[ArgumentHandler::SERVER_EXECUTABLE] = "./r-type_server <IP_ADDRESS> <PORT> [ROOM_BOOLEAN]";
    _hTextList[ArgumentHandler::CLIENT_EXECUTABLE] =
        "./r-type_server <CLIENT_IP_ADDRESS> <CLIENT_PORT> <SERVER_IP_ADDRESS> <SERVER_PORT + 1000>";
}

bool ArgumentHandler::processHOptionVerification(ArgumentHandler::ArgumentFunctionType functionType)
{
    if (_argumentsToParse.size() != 1)
        return false;
    if (_argumentsToParse.at(0) != "-h")
        return false;
    std::cerr << _hTextList[functionType] << std::endl;
    _argumentsToParse.erase(_argumentsToParse.begin());
    return true;
}

ArgumentHandler::ServerInformation ArgumentHandler::extractServerInformation(void)
{
    ArgumentHandler::ServerInformation serverInformation;

    if (processHOptionVerification(ArgumentHandler::SERVER_EXECUTABLE))
        throw ArgumentError("Use of a -h option", "extractServerInformation -> ArgumentHandler.cpp");
    if (_argumentsToParse.size() < 2) {
        std::cerr << _hTextList[ArgumentHandler::SERVER_EXECUTABLE] << std::endl;
        throw ArgumentError("Invalid number of argument. At least 2 needed by the server.",
            "extractServerInformation -> ArgumentHandler.cpp");
    }
    if (_argumentsToParse.size() > 3) {
        std::cerr << _hTextList[ArgumentHandler::SERVER_EXECUTABLE] << std::endl;
        throw ArgumentError("Invalid number of argument. A maximum of 3 arguments are needed by the server.",
            "extractServerInformation -> ArgumentHandler.cpp");
    }
    serverInformation.address = std::string(_argumentsToParse.at(0));
    _argumentsToParse.erase(_argumentsToParse.begin());
    serverInformation.port = std::atoi(_argumentsToParse.at(0).c_str());
    _argumentsToParse.erase(_argumentsToParse.begin());
    if (_argumentsToParse.size() >= 1) {
        std::string value = std::string(_argumentsToParse.at(0));
        boost::algorithm::to_lower(value);
        serverInformation.room = ("true" == value || "1" == value || "yes" == value || "y" == value);
    } else {
        serverInformation.room = false;
    }
    std::cerr << "Server room : " << (serverInformation.room ? "True" : "False") << std::endl;
    if (serverInformation.port == 0) {
        std::cerr << _hTextList[ArgumentHandler::SERVER_EXECUTABLE] << std::endl;
        throw ArgumentError(
            "Invalid args type. Please refer to -h option", "extractServerInformation -> ArgumentHandler.cpp");
    }
    return serverInformation;
}

ArgumentHandler::ClientInformation ArgumentHandler::extractClientInformation(void)
{
    ArgumentHandler::ClientInformation clientInformation;

    if (processHOptionVerification(ArgumentHandler::CLIENT_EXECUTABLE))
        throw ArgumentError("Use of a -h option", "extractClientInformation -> ArgumentHandler.cpp");
    if (_argumentsToParse.size() != 4) {
        std::cerr << _hTextList[ArgumentHandler::CLIENT_EXECUTABLE] << std::endl;
        throw ArgumentError(
            "Invalid number of argument. 4 needed by the client.", "extractClientInformation -> ArgumentHandler.cpp");
    }
    clientInformation.clientAddress = std::string(_argumentsToParse.at(0));
    _argumentsToParse.erase(_argumentsToParse.begin());
    clientInformation.clientPort = std::atoi(_argumentsToParse.at(0).c_str());
    _argumentsToParse.erase(_argumentsToParse.begin());
    clientInformation.serverAddress = std::string(_argumentsToParse.at(0));
    _argumentsToParse.erase(_argumentsToParse.begin());
    clientInformation.serverPort = std::atoi(_argumentsToParse.at(0).c_str());
    _argumentsToParse.erase(_argumentsToParse.begin());
    if (clientInformation.clientPort == 0 || clientInformation.serverPort == 0) {
        std::cerr << _hTextList[ArgumentHandler::CLIENT_EXECUTABLE] << std::endl;
        throw ArgumentError(
            "Invalid args type. Please refer to -h option", "extractClientInformation -> ArgumentHandler.cpp");
    }
    return clientInformation;
}
