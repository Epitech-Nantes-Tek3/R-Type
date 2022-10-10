/*
** EPITECH PROJECT, 2022
** Project
** File description:
** ArgumentHandler
*/

/// @file libs/ArgumentHandler.hpp

#include "ArgumentHandler.hpp"
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
    _hTextList[ArgumentHandler::SERVER_EXECUTABLE] = "./r-type_server <IP_ADDRESS> <PORT>";
    _hTextList[ArgumentHandler::CLIENT_EXECUTABLE] = "./r-type_server <CLIENT_IP_ADDRESS> <CLIENT_PORT> <SERVER_IP_ADDRESS> <SERVER_PORT + 1000>";
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
        throw ArgumentError(
            "Use of a -h option", "extractServerInformation -> ArgumentHandler.cpp");
    if (_argumentsToParse.size() != 2) {
        std::cerr << _hTextList[ArgumentHandler::SERVER_EXECUTABLE] << std::endl;
        throw ArgumentError(
            "Invalid number of argument. 2 needed by the server.", "extractServerInformation -> ArgumentHandler.cpp");
    }
    serverInformation.address = std::string(_argumentsToParse.at(0));
    _argumentsToParse.erase(_argumentsToParse.begin());
    serverInformation.port = std::atoi(_argumentsToParse.at(0).c_str());
    _argumentsToParse.erase(_argumentsToParse.begin());
    if (serverInformation.port == 0) {
        std::cerr << _hTextList[ArgumentHandler::SERVER_EXECUTABLE] << std::endl;
        throw ArgumentError(
            "Invalid args type. Please refer to -h option", "extractServerInformation -> ArgumentHandler.cpp");
    }
    return serverInformation;
}
