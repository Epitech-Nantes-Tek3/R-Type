/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** Client
*/

/// @file Client/ClientRoom.cpp

#include "ClientRoom.hpp"
#include "Error/Error.hpp"
#include "GameComponents/PlayerComponent.hpp"
#include "GameComponents/PositionComponent.hpp"
#include "GameEntityManipulation/CreateEntitiesFunctions/CreateAlliedProjectile.hpp"
#include "Transisthor/TransisthorECSLogic/Both/Components/Networkable.hpp"
#include "Transisthor/TransisthorECSLogic/Client/Components/NetworkServer.hpp"
#include "Transisthor/TransisthorECSLogic/Client/Systems/SendNewlyCreatedToServer.hpp"
#include "Transisthor/TransisthorECSLogic/Client/Systems/SendToServer.hpp"

using namespace error_lib;
using namespace communicator_lib;
using namespace client_data;
using namespace ecs;

ClientRoom::ClientRoom()
{
    _networkInformations = Client();
    _serverEndpoint = Client();
    _communicatorInstance = std::make_shared<Communicator>(_networkInformations);
    _worldInstance = std::make_shared<World>(1);
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

struct Temp : public System {
    /// @brief A useless system used for functional testing purpose
    void run(World &world) { (void)world; }
};

void ClientRoom::initEcsGameData(void)
{
    _worldInstance->addResource<RandomDevice>();
    _worldInstance->addSystem<Temp>();
    _worldInstance->addSystem<SendToServer>();
    _worldInstance->addSystem<SendNewlyCreatedToServer>();
}

void ClientRoom::startConnexionProtocol(void)
{
    _communicatorInstance.get()->startReceiverListening();
    _communicatorInstance.get()->sendDataToAClient(_serverEndpoint, nullptr, 0, 10);
}

void ClientRoom::protocol12Answer(CommunicatorMessage connexionResponse)
{
    _state = ClientState::IN_GAME;
    _worldInstance.get()->addEntity().addComponent<NetworkServer>(connexionResponse.message.clientInfo.getId());
    std::vector<std::shared_ptr<Entity>> joined = _worldInstance.get()->joinEntities<Player>();
    createNewAlliedProjectile(*_worldInstance.get(), *joined[0],
        NewlyCreated().generate_uuid(_worldInstance.get()->getResource<RandomDevice>().getRandomDevice(), 16));
}

void ClientRoom::startLobbyLoop(void)
{
    CommunicatorMessage connexionResponse;

    startConnexionProtocol();
    initEcsGameData();
    _state = ClientState::LOBBY;
    while (_state != ClientState::ENDED && _state != ClientState::UNDEFINED) {
        try {
            connexionResponse = _communicatorInstance.get()->getLastMessage();
            if (connexionResponse.message.type == 11) {
                std::cerr << "No places left inside the wanted room. Please retry later" << std::endl;
                return;
            }
            if (connexionResponse.message.type == 12)
                protocol12Answer(connexionResponse);
        } catch (NetworkError &error) {
        }
        if (_state == ClientState::IN_GAME)
            _worldInstance.get()->runSystems(); /// WILL BE IMPROVED IN PART TWO (THREAD + CLOCK)
    }
}
