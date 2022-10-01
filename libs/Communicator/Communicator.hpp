/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** Communicator
*/

/// @file libs/Communicator/Communicator.hpp

#ifndef COMMUNICATOR_HPP_
#define COMMUNICATOR_HPP_

#include <vector>
#include "Client.hpp"
#include "Receiver.hpp"
#include "Sender.hpp"

namespace communicator_lib
{
    /// @brief Bridge between communicator and server for message
    struct CommunicatorMessage {
        /// @brief The network message
        Message message;
        /// @brief First communication of this client ?
        bool newClient;
    };

    /// @brief Network gestionner
    class Communicator {
      public:
        /// @brief Construct a new Communicator object
        Communicator();

        /// @brief Construct a new Communicator object
        /// @param networkBind Network information for the socket bind
        Communicator(Client networkBind);

        /// @brief Destroy the Communicator object
        ~Communicator();

        /// @brief Get the Client List vector
        /// @return std::vector<Client> The client list vector
        inline std::vector<Client> getClientList(void) const { return _clientList; };

        /// @brief Add a client inside the list of client
        /// @param client The client to add
        /// @throw Throw an error if the client is already on the database (NetworkError)
        void addClientToList(Client &client);

        /// @brief Remove a given client from the list
        /// @param client The matching client to delete
        /// If the client are not found, nothing will be done
        void removeClientFromList(Client &client);

        /// @brief Search and return a client from the list by his information
        /// @param address The address of the client
        /// @param port The port of the client
        /// @return Client& The founded client
        /// @throw Throw an error when no matching client are found (NetworkError)
        Client &getClientFromList(std::string address, long port);

        /// @brief Ask the receiver module to get the last message
        /// @return The last message
        /// @throw Throw an error when no message are found (NetworkError)
        CommunicatorMessage getLastMessage(void);

        /// @brief Ask the receiver module to get the last message of a client
        /// @param client THe wanted client
        /// @return The client message
        /// @throw Throw an error when no message are found (NetworkError)
        CommunicatorMessage getLastMessageFromClient(Client client);

        /// @brief Tell to the client the communication is over. Remove the client from database
        /// @param client The wanted client
        /// @param newEndpoint A potential new endpoint for the client (if newEndpoint == Client() no endpoint will be
        /// transfered)
        void kickAClient(Client client, Client newEndpoint);

        /// @brief Ask the receiver to start the listening process
        inline void startReceiverListening(void) { _receiverModule.startListening(); };

      private:
        /// @brief Send a protocol 20 to a client
        /// @param client The destination
        /// @param newEndpoint The new endpoint to transfer
        void sendProtocol20(Client client, Client newEndpoint);

        /// @brief If the message is a type 2X -> trait it
        /// @param lastMessage The message to trait
        void receiveProtocol2X(Message lastMessage);

        /// @brief Replace a client in the memory by another
        /// @param oldClient The oldest client to replace
        /// @param newClient to replace with
        void replaceClientByAnother(Client oldClient, Client newClient);

        /// @brief List of all the current client
        std::vector<Client> _clientList;

        /// @brief Instance of the sender module
        Sender _senderModule;

        /// @brief Instance of the receiver module
        Receiver _receiverModule;
    };
} // namespace communicator_lib

#endif /* !COMMUNICATOR_HPP_ */
