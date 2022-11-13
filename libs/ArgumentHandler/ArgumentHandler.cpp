/*
** EPITECH PROJECT, 2022
** R-Type
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
    _hTextList[ArgumentHandler::CLIENT_EXECUTABLE] =
        "./r-type_client <CLIENT_IP_ADDRESS> <CLIENT_PORT> <SERVER_IP_ADDRESS> <SERVER_PORT>";
    _hTextList[ArgumentHandler::ROOM_EXECUTABLE] = "./r-type_room <ID> <NAME> <IP_ADDRESS> <PORT>";
    _hTextList[ArgumentHandler::ADMIN_PANEL_EXECUTABLE] = "./r-type_admin_panel <IP_ADDRESS> <PORT>";
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

ArgumentHandler::RoomInformation ArgumentHandler::extractRoomInformations(void)
{
    ArgumentHandler::RoomInformation roomInformations;

    roomInformations.configs = new short[6];
    if (processHOptionVerification(ArgumentHandler::ROOM_EXECUTABLE))
        throw ArgumentError("Use of a -h option", "extractRoomInformations -> ArgumentHandler.cpp");
    if (_argumentsToParse.size() != 10) {
        std::cerr << _hTextList[ArgumentHandler::ROOM_EXECUTABLE] << std::endl;
        throw ArgumentError(
            "Invalid number of argument. 4 needed by the server.", "extractRoomInformations -> ArgumentHandler.cpp");
    }
    long id = std::atol(_argumentsToParse.at(0).c_str());
    if (id < 0) {
        throw ArgumentError("Invalid ID. An ID must be positive.", "extractRoomInformations -> ArgumentHandler.cpp");
    }
    roomInformations.id = id;
    _argumentsToParse.erase(_argumentsToParse.begin());
    std::string name = std::string(_argumentsToParse.at(0).c_str());
    if (name == "") {
        throw ArgumentError(
            "Invalid name. Please enter a non-null name", "extractRoomInformations -> ArgumentHandler.cpp");
    }
    roomInformations.name = name;
    _argumentsToParse.erase(_argumentsToParse.begin());
    roomInformations.address = std::string(_argumentsToParse.at(0));
    _argumentsToParse.erase(_argumentsToParse.begin());
    roomInformations.port = std::atoi(_argumentsToParse.at(0).c_str());
    _argumentsToParse.erase(_argumentsToParse.begin());
    for (int i = 0; i < 6; i++) {
        roomInformations.configs[i] = std::atoi(_argumentsToParse.at(0).c_str());
        _argumentsToParse.erase(_argumentsToParse.begin());
    }
    if (roomInformations.port == 0) {
        std::cerr << _hTextList[ArgumentHandler::ROOM_EXECUTABLE] << std::endl;
        throw ArgumentError(
            "Invalid args type. Please refer to -h option", "extractRoomInformations -> ArgumentHandler.cpp");
    }
    return roomInformations;
}
