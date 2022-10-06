/*
** EPITECH PROJECT, 2022
** Project
** File description:
** Room
*/

/// @file Server/Room.hpp

#ifndef ROOM_HPP_
#define ROOM_HPP_

#include "Communicator/Client.hpp"

using namespace communicator_lib;

namespace server_data
{
    /// @brief Place where the game run (Like a lobby). Hold all libraries instance.
    class Room {
      public:
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
        inline unsigned short getRoomId(void) { return _id; };

      private:
        /// @brief Id of the room. (Used by the server)
        unsigned short _id;

        /// @brief Network informations of the Room.
        Client _networkInformations;
    };
} // namespace server_data

#endif /* !ROOM_HPP_ */
