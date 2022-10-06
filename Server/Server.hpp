/*
** EPITECH PROJECT, 2022
** Project
** File description:
** Server
*/

/// @file Server/Server.hpp

#ifndef SERVER_HPP_
#define SERVER_HPP_

#include "Room.hpp"
#include "Communicator/Client.hpp"
#include <vector>

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
        void createANewRoom(void);

      private:
        /// @brief List of all the active room.
        std::vector<Room> _activeRoomList;

        /// @brief Network information of the server. Setup at the construction
        Client _networkInformations;
    };
} // namespace server_data

#endif /* !SERVER_HPP_ */
