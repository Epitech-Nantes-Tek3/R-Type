/*
** EPITECH PROJECT, 2022
** Project
** File description:
** Communicator
*/

/// @file libs/Communicator/Communicator.hpp

#ifndef COMMUNICATOR_HPP_
#define COMMUNICATOR_HPP_

#include <vector>
#include "Client.hpp"
#include "Sender.hpp"

namespace communicator_lib
{
    /// @brief Network gestionner
    class Communicator {
      public:
        /// @brief Construct a new Communicator object
        Communicator();

        /// @brief Destroy the Communicator object
        ~Communicator();

        /// @brief Get the Client List vector
        /// @return std::vector<Client> The client list vector
        std::vector<Client> getClientList(void) const;

        /// @brief Add a client inside the list of client
        /// @param client The client to add
        /// If the client is already inside the list, nothing will be done (Logging in std::cerr)
        void addClientToList(Client &client);

        /// @brief Remove a given client from the list
        /// @param client The matching client to delete
        /// If the client are not found, nothing will be done
        void removeClientFromList(Client &client);

        /// @brief Search and return a client from the list by his information
        /// @param address The address of the client
        /// @param port The port of the client
        /// @return Client& The founded client
        /// @throw Throw an error when no matching client are found (to update when error class have been setup)
        Client &getClientFromList(std::string address, long port);

      private:
        /// @brief List of all the current client
        std::vector<Client> _clientList;
        /// @brief Instance of the sender module
        Sender _senderModule;
    };
} // namespace communicator_lib

#endif /* !COMMUNICATOR_HPP_ */
