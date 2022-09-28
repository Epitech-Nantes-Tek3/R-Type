/*
** EPITECH PROJECT, 2022
** Project
** File description:
** Sender
*/

/// @file libs/Communicator/Sender.hpp

#ifndef SENDER_HPP_
#define SENDER_HPP_

#include "Client.hpp"
#include <vector>

namespace communicator_lib
{
    /// @brief Sending data module
    class Sender
    {
    public:
        /// @brief The sender object constructor
        Sender();

        /// @brief Destroy the Sender object
        ~Sender();

        /// @brief Send data to a given client
        /// @param client The client informations
        /// @param data The given data to transfer
        void sendDataToAClient(Client &client, void *data);

        /// @brief Send data to a given vector of clients
        /// @param clients The clients informations vector
        /// @param data The given data to transfer
        void sendDataToMultipleClients(std::vector<Client> clients, void *data);
    };
}

#endif /* !SENDER_HPP_ */
