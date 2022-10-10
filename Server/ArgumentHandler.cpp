/*
** EPITECH PROJECT, 2022
** Project
** File description:
** ArgumentHandler
*/

#include "ArgumentHandler.hpp"
#include <iostream>
#include "Error/Error.hpp"

using namespace server_data;
using namespace error_lib;

ArgumentHandler::ArgumentHandler()
{
    _argumentsToParse = {};
    bindAllHOptionText();
}

ArgumentHandler::ArgumentHandler(const int ac, const char **av)
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
}

bool ArgumentHandler::processHOptionVerification(ArgumentHandler::ArgumentFunctionType functionType)
{
    if (_argumentsToParse.size() != 1)
        return false;
    if (_argumentsToParse.at(0) != "-h")
        return false;
    std::cerr << _hTextList[functionType] << std::endl;
    _argumentsToParse.emplace(_argumentsToParse.begin());
    return true;
}

ArgumentHandler::ServerInformation ArgumentHandler::extractServerInformation(void)
{
    ArgumentHandler::ServerInformation serverInformation;
    /// ADD -H GESTION
    if (_argumentsToParse.size() != 2) {
        std::cerr << _hTextList[ArgumentHandler::SERVER_EXECUTABLE] << std::endl;
        throw ArgumentError(
            "Invalid number of argument. 2 needed by the server.", "extractServerInformation -> ArgumentHandler.cpp");
    }
    serverInformation.address = std::string(_argumentsToParse.at(0));
    _argumentsToParse.emplace(_argumentsToParse.begin());
    serverInformation.port = std::atoi(_argumentsToParse.at(0).c_str());
    if (serverInformation.port == 0) {
        std::cerr << _hTextList[ArgumentHandler::SERVER_EXECUTABLE] << std::endl;
        throw ArgumentError(
            "Invalid args type. Please refer to -h option", "extractServerInformation -> ArgumentHandler.cpp");
    }
    return serverInformation;
}
