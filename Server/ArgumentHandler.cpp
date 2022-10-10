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

ArgumentHandler::ArgumentHandler() { _argumentsToParse = {}; }

ArgumentHandler::ArgumentHandler(const int ac, const char **av)
{
    _argumentsToParse = {};
    for (int i = 1; i < ac; i++) {
        _argumentsToParse.push_back(std::string(av[i]));
    }
}

ArgumentHandler::ServerInformation ArgumentHandler::extractServerInformation(void)
{
    /// ADD -H GESTION
    if (_argumentsToParse.size() != 2) {
        std::cerr << "Invalid number of argument sended. Please refer to -h option" << std::endl;
        /// ADD -h display call.
        throw ArgumentError(
            "Invalid number of argument. 2 needed by the server.", "extractServerInformation -> ArgumentHandler.cpp");
    }
    return {"", 0};
}