/*
** EPITECH PROJECT, 2022
** Project
** File description:
** Client
*/

/// @file Client/ClientRoom.hpp

#ifndef CLIENT_ROOM_HPP_
#define CLIENT_ROOM_HPP_

#include <memory>
#include "Communicator/Client.hpp"
#include "Communicator/Communicator.hpp"
#include "Transisthor/Transisthor.hpp"
#include "World/World.hpp"

using namespace communicator_lib;
using namespace ecs;
using namespace transisthor_lib;

namespace client_data
{
    /// @brief Place where the game run (Like a lobby). Hold all libraries instance,
    class ClientRoom {
      public:

        /// @brief All the possible state of a client
        enum ClientState {
            UNDEFINED,
            LOBBY,
            IN_GAME,
            ENDED
        };

        /// @brief Construct a new Client with default value
        ClientRoom();

        /// @brief Construct a new Client object
        /// @param networkInformations Network informations of the client
        ClientRoom(Client networkInformations);

        /// @brief Destroy the Client object
        ~ClientRoom() = default;

      private:
        /// @brief Network informations of the room.
        Client _networkInformations;

        /// @brief Instance of the communicator library
        std::shared_ptr<Communicator> _communicatorInstance;

        /// @brief Instance of the transisthor library
        std::shared_ptr<Transisthor> _transisthorInstance;

        /// @brief Instance of the ECS library
        std::shared_ptr<World> _worldInstance;

        /// @brief Current state of the client
        ClientState _state;
    };
} // namespace client_data

#endif /* !CLIENT_HPP_ */
