/*
** EPITECH PROJECT, 2022
** Project
** File description:
** Client
*/

/// @file Client/ClientRoom.cpp

#include "ClientRoom.hpp"
#include "Error/Error.hpp"

using namespace error_lib;
using namespace communicator_lib;
using namespace client_data;

ClientRoom::ClientRoom()
{
    _networkInformations = Client();
    _serverEndpoint = Client();
    _communicatorInstance = std::make_shared<Communicator>(_networkInformations);
    _worldInstance = std::make_shared<World>(1);
    _transisthorInstance = std::make_shared<Transisthor>(*(_communicatorInstance.get()), *(_worldInstance.get()));
    _communicatorInstance.get()->updateTransisthorBridge(_transisthorInstance);
    _worldInstance.get()->updateTransisthorBridge(_communicatorInstance.get()->getTransisthorBridge());
    _state = ClientState::UNDEFINED;
}

ClientRoom::ClientRoom(std::string address, unsigned short port, std::string serverAddress, unsigned short serverPort)
{
    _networkInformations = Client(address, port);
    _serverEndpoint = Client(serverAddress, serverPort);
    _communicatorInstance = std::make_shared<Communicator>(_networkInformations);
    _worldInstance = std::make_shared<World>(1);
    _transisthorInstance = std::make_shared<Transisthor>(*(_communicatorInstance.get()), *(_worldInstance.get()));
    _communicatorInstance.get()->updateTransisthorBridge(_transisthorInstance);
    _worldInstance.get()->updateTransisthorBridge(_communicatorInstance.get()->getTransisthorBridge());
    _state = ClientState::UNDEFINED;
}

void ClientRoom::startLobbyLoop(void)
{
    CommunicatorMessage connexionResponse;

    _communicatorInstance.get()->startReceiverListening();
    _communicatorInstance.get()->sendDataToAClient(_serverEndpoint, nullptr, 0, 10);
    _state = ClientState::LOBBY;
    while (_state != ClientState::ENDED && _state != ClientState::UNDEFINED) {
        try {
            connexionResponse = _communicatorInstance.get()->getLastMessage();
            if (connexionResponse.message.type == 30)
                std::cerr << "Component succesfully received." << std::endl; /// USED FOR FUNCTIONAL TESTING, WILL BE REMOVED LATER
            std::cerr << "ClientRoom received a connexion protocol answer."
                      << std::endl; /// WILL BE DELETED WITH CONNEXION PROTOCOL ISSUE
        } catch (NetworkError &error) {
        }
        _worldInstance.get()->runSystems(); /// WILL BE IMPROVED IN PART TWO (THREAD + CLOCK)
    }
}