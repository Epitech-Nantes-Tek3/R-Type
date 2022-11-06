/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** AdminPanel
*/

#include "AdminPanel.hpp"
#include "Error/Error.hpp"

using namespace error_lib;
using namespace communicator_lib;
using namespace admin_panel;

AdminPanel::AdminPanel(std::string address, unsigned short port, std::string serverAddress, unsigned short serverPort)
{
    _networkInformations = Client(address, port);
    _communicatorInstance = std::make_shared<Communicator>(_networkInformations);
    _serverEndpoint = Client(serverAddress, serverPort);
    _waitingForAnswer = false;
    _isAuth = false;
    _pseudo = "";
    _state = true;
}

void AdminPanel::startLoop()
{
    _communicatorInstance->startReceiverListening();
    while (_state) {
        try {
            auto databaseAnswer = _communicatorInstance.get()->getLastMessage();
            if (databaseAnswer.message.type == 11) {
                std::cerr << "Invalid login, please retry." << std::endl;
                return;
            }
            if (databaseAnswer.message.type == 15) {
                _communicatorInstance->utilitaryAskForADatabaseValue(_pseudo, "Moderator", {0});
            }
            if (databaseAnswer.message.type == 41)
                _handleAReceivedData(databaseAnswer);
        } catch (NetworkError &error) {
        }
        if (!_waitingForAnswer) {
            if (!_isAuth) {
                _authentificationProcess();
            } else {
                _getARequest();
            }
        }
    }
}

void AdminPanel::_authentificationProcess()
{
    std::string pseudo;
    std::string password;

    std::cout << "Welcome to the Admin panel !" << std::endl;
    std::cout << "Please refer your name : ";
    std::cin >> pseudo;
    std::cout << "Welcome : " << pseudo << " ! Now, your password : ";
    std::cin >> password;
    void *networkData = std::malloc(sizeof(char) * 10);

    if (networkData == nullptr)
        throw MallocError("Malloc failed.");
    std::memcpy(networkData, pseudo.c_str(), sizeof(char) * 5);
    std::memcpy((void *)((char *)networkData + sizeof(char) * 5), password.c_str(), sizeof(char) * 5);
    _communicatorInstance.get()->sendDataToAClient(_serverEndpoint, networkData, sizeof(char) * 10, 14);
    std::free(networkData);
    _pseudo = pseudo;
    _waitingForAnswer = true;
    std::cout << "Request send to the server, please wait." << std::endl;
}

void AdminPanel::_handleAReceivedData(CommunicatorMessage databaseAnswer)
{
    std::string value = _communicatorInstance->utilitaryReceiveDatabaseValue(databaseAnswer);

    _waitingForAnswer = false;
    if (!_isAuth) {
        if (value != "1") {
            std::cerr << "Your note an admin user ;)" << std::endl;
        } else {
            std::cerr << "Authentification succeed." << std::endl;
            _isAuth = true;
        }
        return;
    }
}

void AdminPanel::_getARequest() {}