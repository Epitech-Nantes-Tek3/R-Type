/*
** EPITECH PROJECT, 2022
** Project
** File description:
** ArgumentHandler
*/

#include "ArgumentHandler.hpp"

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
