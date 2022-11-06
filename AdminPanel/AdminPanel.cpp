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

std::vector<AdminPanel::PanelCommand> commandList = {{"updatePassword", "", {}}, {"updateName", "", {}},
    {"ban", "", {}}, {"mute", "", {}}, {"unban", "", {}}, {"unmute", "", {}}, {"delete", "", {}}, {"promote", "", {}},
    {"unpromote", "", {}}, {"get", "", {}}};

AdminPanel::AdminPanel(std::string address, unsigned short port, std::string serverAddress, unsigned short serverPort)
{
    _networkInformations = Client(address, port);
    _communicatorInstance = std::make_shared<Communicator>(_networkInformations);
    _serverEndpoint = Client(serverAddress, serverPort);
    _waitingForAnswer = false;
    _isAuth = false;
    _pseudo = "";
    _state = true;
    _requestAction["updatePassword"] = std::bind(&AdminPanel::_updatePasswordAction, this, std::placeholders::_1);
    _requestAction["updateName"] = std::bind(&AdminPanel::_updateNameAction, this, std::placeholders::_1);
    _requestAction["ban"] = std::bind(&AdminPanel::_banAction, this, std::placeholders::_1);
    _requestAction["unban"] = std::bind(&AdminPanel::_unbanAction, this, std::placeholders::_1);
}

void AdminPanel::startLoop()
{
    _communicatorInstance->startReceiverListening();
    while (_state) {
        try {
            auto databaseAnswer = _communicatorInstance.get()->getLastMessage();
            if (databaseAnswer.message.type == 11) {
                std::cout << "Invalid login, please retry." << std::endl;
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
            std::cout << "Your note an admin user ;)" << std::endl;
        } else {
            std::cout << "Authentification succeed." << std::endl;
            _isAuth = true;
        }
        return;
    }
    std::cout << value << std::endl;
}

AdminPanel::PanelCommand AdminPanel::_parseAClientRequest(std::string clientRequest)
{
    AdminPanel::PanelCommand panelCommand;
    std::string delimiter = " ";
    size_t pos = 0;
    std::string token;
    std::size_t counter = 0;

    while ((pos = clientRequest.find(delimiter)) != std::string::npos) {
        token = clientRequest.substr(0, pos);
        if (counter == 0)
            panelCommand.keyWord = std::string(token);
        if (counter == 1)
            panelCommand.userName = std::string(token);
        if (counter >= 2)
            panelCommand.options.push_back(std::string(token));
        clientRequest.erase(0, pos + delimiter.length());
        counter++;
    }
    if (counter == 0)
        panelCommand.keyWord = std::string(clientRequest);
    if (counter == 1)
        panelCommand.userName = std::string(clientRequest);
    if (counter >= 2)
        panelCommand.options.push_back(std::string(clientRequest));
    return panelCommand;
}

void AdminPanel::_getARequest()
{
    std::string clientRequest;

    std::cout << "Enter your request : ";
    std::getline(std::cin, clientRequest);
    AdminPanel::PanelCommand parsedRequest = _parseAClientRequest(clientRequest);
    if (_requestAction.find(parsedRequest.keyWord) == _requestAction.end()) {
        std::cout << "This is not a valid command. Please refer to the Notion protocol." << std::endl;
        return;
    }
    _requestAction[parsedRequest.keyWord](parsedRequest);
}

void AdminPanel::_updatePasswordAction(AdminPanel::PanelCommand parsedRequest)
{
    if (parsedRequest.options.size() != 2) {
        std::cout << "Invalid command parameters. Please refer to the Notion protocol." << std::endl;
    }
    //_communicatorInstance->utilitarySetADatabaseValue(
    // parsedRequest.userName, "Password", parsedRequest.options.at(1), {0});
    /// WILL BE ADDED LATER
}

void AdminPanel::_updateNameAction(AdminPanel::PanelCommand parsedRequest)
{
    if (parsedRequest.options.size() != 1) {
        std::cout << "Invalid command parameters. Please refer to the Notion protocol." << std::endl;
    }
    //_communicatorInstance->utilitarySetADatabaseValue(
    // parsedRequest.userName, "UserName", parsedRequest.options.at(0), {0});
    /// WILL BE ADDED LATER
}

void AdminPanel::_banAction(AdminPanel::PanelCommand parsedRequest)
{
    if (parsedRequest.userName == "") {
        std::cout << "Invalid command parameters. Please refer to the Notion protocol." << std::endl;
    }
    _communicatorInstance->utilitarySetADatabaseValue(parsedRequest.userName, 1, 1, {0});
}

void AdminPanel::_unbanAction(AdminPanel::PanelCommand parsedRequest)
{
    if (parsedRequest.userName == "") {
        std::cout << "Invalid command parameters. Please refer to the Notion protocol." << std::endl;
    }
    _communicatorInstance->utilitarySetADatabaseValue(parsedRequest.userName, 1, 0, {0});
}