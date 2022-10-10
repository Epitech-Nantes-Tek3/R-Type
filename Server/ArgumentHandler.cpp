/*
** EPITECH PROJECT, 2022
** Project
** File description:
** ArgumentHandler
*/

#include "ArgumentHandler.hpp"
#include <iostream>

using namespace server_data;

ArgumentHandler::ArgumentHandler()
{
    _argumentsToParse = {};
}

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
        /// THROW A CUSTOM ERROR
    }
    return {"", 0};
}