/*
** EPITECH PROJECT, 2022
** Project
** File description:
** Receiver
*/

/// @file libs/Communicator/Receiver.hpp

#ifndef RECEIVER_HPP_
#define RECEIVER_HPP_

#include <boost/array.hpp>
#include <boost/asio.hpp>
#include <vector>
#include "Client.hpp"

namespace communicator_lib
{
    /// @brief A network data
    struct Message {
        /// @brief Sender information
        Client client_info;
        /// @brief The message content
        void *data;
        /// @brief Size of the message
        size_t size;
    };

    /// @brief Get and store all the network message
    class Receiver {
      public:
        /// @brief Construct a new Receiver object (Default version)
        Receiver();

        /// @brief Construct a new Receiver object
        /// @param networkData The wanted network data
        Receiver(Client networkData);

        /// @brief Destroy the Receiver object
        ~Receiver();

        /// @brief Get the message list vector
        /// @return The message list vector
        std::vector<Message> getMessageList(void) const;

        /// @brief Set the message list vector
        /// @param newMessageList The new message vector
        void setMessageList(std::vector<Message> newMessageList);

        /// @brief Get the network data value
        /// @return The network data value
        Client getNetworkData(void) const;

        /// @brief Set the network data value
        /// @param newNetworkData The new network data value
        void setNetworkData(Client newNetworkData);

        /// @brief Add a new message inside the list
        /// @param message The message to add
        void addMessage(Message message);

        /// @brief Get the size of the message list
        /// @return The message list size
        int getMessageListSize(void) const;

        /// @brief Pop the first message of the list (oldest)
        /// @return The older message
        /// @throw Throw an error when no message are found (to update when error class have been setup)
        Message getLastMessage(void);

        /// @brief Pop the oldest message of a client inside the list
        /// @param client The wanted client
        /// @return The client message
        /// @throw Throw an error when no message are found (to update when error class have been setup)
        Message getLastMessageFromClient(Client client);

        /// @brief Remove all the messages of a client
        /// @param client The wanted client
        /// If no matching message is found, nothing happen.
        void removeAllClientMessage(Client client);

        /// @brief Start the listening process
        void startListening(void);

      protected:
      private:
        /// @brief Private function called when a data arrived
        /// @param error A possible error code from the network
        /// @param bytes_transferred Size of the transfered data
        void handleReceive(const boost::system::error_code &error, size_t bytesTransferred);

        /// @brief Private async function holding the network search process
        void wait(void);

        /// @brief List of all the untraited message
        std::vector<Message> _messageList;

        /// @brief Network information of the receiver
        Client _networkData;

        /// @brief Context for boost
        boost::asio::io_service _ioService;

        /// @brief The socket for transferring data
        boost::asio::ip::udp::socket _socket{_ioService};

        /// @brief A temporary data using in the listening functionnality
        boost::array<void *, 100000> _tempData;

        /// @brief A temporary data using in the listening functionnality
        boost::asio::ip::udp::endpoint _tempRemoteEndpoint;
    };
} // namespace communicator_lib

#endif /* !RECEIVER_HPP_ */
