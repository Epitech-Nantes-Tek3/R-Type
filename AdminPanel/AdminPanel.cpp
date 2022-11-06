/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** AdminPanel
*/

#include "Error/Error.hpp"
#include "AdminPanel.hpp"

using namespace error_lib;
using namespace communicator_lib;
using namespace admin_panel;

AdminPanel::AdminPanel(std::string address, unsigned short port)
{
    _networkInformations = Client(address, port);
    _communicatorInstance = std::make_shared<Communicator>(_networkInformations);
}

void AdminPanel::startLoop()
{
    bool state = true;
    _communicatorInstance->startReceiverListening();
    while (state) {
        try {
            auto databaseAnswer = _communicatorInstance.get()->getLastMessage();
            (void)databaseAnswer;
        } catch (NetworkError &error) {
        }
    }
}
