/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** Room
*/

/// @file Server/Room.cpp

#include "Room.hpp"
#include "Error/Error.hpp"
#include "GameComponents/PositionComponent.hpp"
#include "GameEntityManipulation/CreateEntitiesFunctions/CreateObstacle.hpp"

using namespace server_data;
using namespace error_lib;
using namespace communicator_lib;
using namespace ecs;

Room::Room()
{
    _id = 0;
    _networkInformations = Client();
    _communicatorInstance = std::make_shared<Communicator>(_networkInformations);
    _worldInstance = std::make_shared<World>(1);
    _transisthorInstance = std::make_shared<Transisthor>(*(_communicatorInstance.get()), *(_worldInstance.get()));
    _communicatorInstance.get()->setTransisthorBridge(_transisthorInstance);
    _worldInstance.get()->setTransisthorBridge(_communicatorInstance.get()->getTransisthorBridge());
    _state = RoomState::UNDEFINED;
}

Room::Room(unsigned short id, Client networkInformations)
{
    _id = id;
    _networkInformations = networkInformations;
    _communicatorInstance = std::make_shared<Communicator>(_networkInformations);
    _worldInstance = std::make_shared<World>(1);
    _transisthorInstance = std::make_shared<Transisthor>(*(_communicatorInstance.get()), *(_worldInstance.get()));
    _communicatorInstance.get()->setTransisthorBridge(_transisthorInstance);
    _worldInstance.get()->setTransisthorBridge(_communicatorInstance.get()->getTransisthorBridge());
    _state = RoomState::UNDEFINED;
}

void Room::startLobbyLoop(void)
{
    CommunicatorMessage connexionDemand;
    Position pos = Position(90, 90);

    _communicatorInstance.get()->startReceiverListening();
    _state = RoomState::LOBBY;
    while (_state != RoomState::ENDED && _state != RoomState::UNDEFINED) {
        try {
            connexionDemand = _communicatorInstance.get()->getLastMessage();
            std::cerr << "Room " << _id << " received a connexion protocol."
                      << std::endl; /// WILL BE DELETED WITH CONNEXION PROTOCOL ISSUE
            _transisthorInstance.get()->transitEcsDataToNetworkData<Position>(1, 6, pos,
                {connexionDemand.message.clientInfo.getId()}); /// USED FOR FUNCTIONNAL TESTING, WILL BE REMOVED LATER

            std::size_t entityId = createNewObstacle(
                *(_worldInstance.get()), 10, 120, 5); /// USED FOR FUNCTIONNAL TESTING, WILL BE REMOVED LATER
            Position entityPosition =
                _worldInstance.get()
                    ->getEntity(entityId)
                    .getComponent<Position>(); /// USED FOR FUNCTIONNAL TESTING, WILL BE REMOVED LATER

            _transisthorInstance.get()->transitEcsDataToNetworkDataEntityObstacle(entityId, entityPosition.x,
                entityPosition.y,
                {connexionDemand.message.clientInfo.getId()}); /// USED FOR FUNCTIONNAL TESTING, WILL BE REMOVED LATER
        } catch (NetworkError &error) {
        }
        _worldInstance.get()->runSystems(); /// WILL BE IMPROVED IN PART TWO (THREAD + CLOCK)
    }
}
