/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** Server
*/

/// @file Server/Server.hpp

#ifndef SERVER_HPP_
#define SERVER_HPP_

#include <vector>
#include "Communicator/Client.hpp"
#include "Communicator/Communicator.hpp"
#include "Room.hpp"

using namespace communicator_lib;

namespace server_data
{
    /// @brief Main class of the server part. Hold room process.
    class Server {
      public:
        /// @brief Construct a new server object
        /// @param address Ip address of the server
        /// @param port Listening port for network process
        Server(std::string address, unsigned short port);

        /// @brief Construct a new server object with default value
        Server();

        /// @brief Destroy the Server object
        ~Server() = default;

        /// @brief Create and add a new Room inside the room list
        /// @param name of the room
        /// @return Id of the newly created room
        unsigned short createANewRoom(std::string name);

        /// @brief Remove and delete a room of the list
        /// @param id of the room to be deleted
        void deleteARoom(unsigned short id);

      private:
        /// @brief List of all the active room.
        std::vector<Room> _activeRoomList;

        /// @brief Network information of the server. Setup at the construction
        Client _networkInformations;

        /// @brief Instance of the communicator library
        Communicator _communicatorInstance;
    };
} // namespace server_data

#endif /* !SERVER_HPP_ */
