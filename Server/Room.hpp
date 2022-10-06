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
#include "Communicator/Communicator.hpp"
#include "Transisthor/Transisthor.hpp"
#include "World/World.hpp"
#include <memory>

using namespace communicator_lib;
using namespace ecs;
using namespace transisthor_lib;

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
        ~Room();

        /// @brief Get the room id
        /// @return The room id
        inline unsigned short getRoomId(void) const { return _id; };

      private:
        /// @brief Id of the room. (Used by the server)
        unsigned short _id;

        /// @brief Network informations of the Room.
        Client _networkInformations;

        /// @brief Instance of the communicator library.
        Communicator *_communicatorInstance;

        /// @brief Instance of the transisthor library.
        Transisthor *_transisthorInstance;

        /// @brief Instance of the ECS library.
        World *_worldInstance;
    };

    /// @brief Overload of the == operator to compare two rooms
    /// @param left param of the comparison
    /// @param right param of the comparison
    /// @return true If the two rooms have the same id
    /// @return false If the two rooms have different id
    inline bool operator==(const Room &left, const Room &right)
    {
        return ((left.getRoomId() == right.getRoomId()));
    }
} // namespace server_data

#endif /* !ROOM_HPP_ */
