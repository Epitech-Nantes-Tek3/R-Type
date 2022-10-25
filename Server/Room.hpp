/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** Room
*/

/// @file Server/Room.hpp

#ifndef ROOM_HPP_
#define ROOM_HPP_

#include <memory>
#include "Communicator/Client.hpp"
#include "Communicator/Communicator.hpp"
#include "Transisthor/Transisthor.hpp"
#include "World/World.hpp"

using namespace communicator_lib;
using namespace ecs;
using namespace transisthor_lib;

namespace server_data
{
    /// @brief Place where the game run (Like a lobby). Hold all libraries instance.
    class Room {
      public:
        /// @brief All the possible state of a room
        enum RoomState { UNDEFINED, LOBBY, IN_GAME, ENDED };

        /// @brief Construct a new Room object with default value
        Room();

        /// @brief Construct a new Room object
        /// @param id Id of the room
        /// @param networkInformation Network informations of the room
        Room(unsigned short id, Client networkInformations);

        /// @brief Destroy the Room object
        ~Room() = default;

        /// @brief Get the room id
        /// @return The room id
        inline unsigned short getRoomId(void) const { return _id; };

        /// @brief Start the loop function of the room. Warning, call it inside a thread
        void startLobbyLoop(void);

      private:
        /// @brief Id of the room. (Used by the server)
        unsigned short _id;

        /// @brief Network informations of the Room.
        Client _networkInformations;

        /// @brief Instance of the communicator library.
        std::shared_ptr<Communicator> _communicatorInstance;

        /// @brief Instance of the transisthor library.
        std::shared_ptr<Transisthor> _transisthorInstance;

        /// @brief Instance of the ECS library.
        std::shared_ptr<World> _worldInstance;

        /// @brief Current state of the room
        RoomState _state;

        /// @brief Number of remaining places inside the room
        unsigned short _remainingPlaces;

        /// @brief Trait a disconnection request. Identify the player and add to it a disconnection component
        /// @param communicatorMessage actual message data
        void _holdADisconnectionRequest(CommunicatorMessage disconectionDemand);

        /// @brief Trait a connexion request. If there is less than 3 players already in the room, send a protocol 22 to
        /// the client. Otherwise, send a 21.
        /// @param communicatorMessage actual message data
        void holdANewConnexionRequest(CommunicatorMessage communicatorMessage);

        /// @brief Init the Ressources and Systems of the ECS
        void initEcsGameData(void);

        /// @brief Start the connexion protocol and ask the server for a place inside the room
        void startConnexionProtocol(void);
    };

    /// @brief Overload of the == operator to compare two rooms
    /// @param left param of the comparison
    /// @param right param of the comparison
    /// @return true If the two rooms have the same id
    /// @return false If the two rooms have different id
    inline bool operator==(const Room &left, const Room &right) { return ((left.getRoomId() == right.getRoomId())); }
} // namespace server_data

#endif /* !ROOM_HPP_ */
