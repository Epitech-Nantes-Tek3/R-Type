/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** Client
*/

/// @file Client/ClientRoom.cpp

#include "ClientRoom.hpp"
#include "Error/Error.hpp"
#include "GameSharedResources/GameClock.hpp"
#include "GameSharedResources/Random.hpp"
#include "SFMLResource/GraphicsFontResource.hpp"
#include "SFMLResource/GraphicsTextureResource.hpp"
#include "SFMLResource/RenderWindowResource.hpp"

using namespace error_lib;
using namespace communicator_lib;
using namespace client_data;

ClientRoom::ClientRoom()
{
    _networkInformations = Client();
    _serverEndpoint = Client();
    _communicatorInstance = std::make_shared<Communicator>(_networkInformations);
    _worldInstance = std::make_shared<World>(1);
    _initSharedResources();
    _transisthorInstance = std::make_shared<Transisthor>(*(_communicatorInstance.get()), *(_worldInstance.get()));
    _communicatorInstance.get()->setTransisthorBridge(_transisthorInstance);
    _worldInstance.get()->setTransisthorBridge(_communicatorInstance.get()->getTransisthorBridge());
    _state = ClientState::UNDEFINED;
}

ClientRoom::ClientRoom(std::string address, unsigned short port, std::string serverAddress, unsigned short serverPort)
{
    _networkInformations = Client(address, port);
    _serverEndpoint = Client(serverAddress, serverPort);
    _communicatorInstance = std::make_shared<Communicator>(_networkInformations);
    _worldInstance = std::make_shared<World>(1);
    _transisthorInstance = std::make_shared<Transisthor>(*(_communicatorInstance.get()), *(_worldInstance.get()));
    _communicatorInstance.get()->setTransisthorBridge(_transisthorInstance);
    _worldInstance.get()->setTransisthorBridge(_communicatorInstance.get()->getTransisthorBridge());
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
            std::cerr << "ClientRoom received a connexion protocol answer."
                      << std::endl; /// WILL BE DELETED WITH CONNEXION PROTOCOL ISSUE
        } catch (NetworkError &error) {
        }
        _worldInstance.get()->runSystems(); /// WILL BE IMPROVED IN PART TWO (THREAD + CLOCK)
    }
}

void ClientRoom::_initSharedResources()
{
    _worldInstance->addResource<GameClock>();
    _worldInstance->addResource<RandomDevice>();
    _worldInstance->addResource<RenderWindowResource>();
    _worldInstance->addResource<GraphicsFontResource>("assets/arial.ttf");
}
