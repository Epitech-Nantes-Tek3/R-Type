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

namespace communicator_lib
{
    /// @brief Network gestionner
    class Communicator
    {
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
        void addClientToList(Client &client);

        /// @brief Remove a given client from the list
        /// @param client The matching client to delete
        void removeClientFromList(Client &client);

        /// @brief Search and return a client from the list by his information
        /// @param address The address of the client
        /// @param port The port of the client
        /// @return Client& The founded client
        Client &getClientFromList(std::string address, long port);

    private:
        /// @brief List of all the current client
        std::vector<Client> _clientList;
    };
}

#endif /* !COMMUNICATOR_HPP_ */
