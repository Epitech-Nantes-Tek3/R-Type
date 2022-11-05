/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** Receiver
*/

/// @file libs/Communicator/Receiver.hpp

#ifndef RECEIVER_HPP_
#define RECEIVER_HPP_

#include <boost/array.hpp>
#include <boost/asio.hpp>
#include <map>
#include <vector>
#include "Client.hpp"

namespace communicator_lib
{
    /// @brief A network data
    struct Message {
        /// @brief Sender information
        Client clientInfo;
        /// @brief The message content
        void *data;
        /// @brief Size of the message
        size_t size;
        /// @brief Data type (Refer to the RFC)
        unsigned short type;
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
        inline std::vector<Message> getMessageList(void) const { return _messageList; };

        /// @brief Set the message list vector
        /// @param newMessageList The new message vector
        inline void setMessageList(std::vector<Message> newMessageList) { _messageList = newMessageList; };

        /// @brief Get the network data value
        /// @return The network data value
        inline Client getNetworkData(void) const { return _networkData; };

        /// @brief Set the network data value
        /// @param newNetworkData The new network data value
        inline void setNetworkData(Client newNetworkData) { _networkData = newNetworkData; };

        /// @brief Add a new message inside the list
        /// @param message The message to add
        inline void addMessage(Message message) { _messageList.push_back(message); };

        /// @brief Get the size of the message list
        /// @return The message list size
        inline int getMessageListSize(void) const { return _messageList.size(); };

        /// @brief Pop the first message of the list (oldest)
        /// @return The older message
        /// @throw Throw an error when no message are found (NetworkError)
        Message getLastMessage(void);

        /// @brief Pop the oldest message of a client inside the list
        /// @param client The wanted client
        /// @return The client message
        /// @throw Throw an error when no message are found (NetworkError)
        Message getLastMessageFromClient(Client client);

        /// @brief Remove all the messages of a client
        /// @param client The wanted client
        /// If no matching message is found, nothing happen.
        void removeAllClientMessage(Client client);

        /// @brief Start the listening process
        /// @throw Throw and error when bind failed (NetworkError)
        void startListening(void);

      protected:
      private:
        /// @brief Private function called when a data arrived
        /// @param error A possible error code from the network
        /// @param bytes_transferred Size of the transfered data
        void handleReceive(const boost::system::error_code &error, size_t bytesTransferred);

        /// @brief Private async function holding the network search process
        void wait(void);

        /// @brief Extract the communication header from the transfered data
        /// @param data The transfered data
        /// @return A vector of two unsigned short which represent the data header
        std::vector<unsigned short> getDataHeader(void *data);

        /// @brief The function will process the data according to the protocol 10
        /// @param dataContent The transfered data (Client + Data)
        void dataTraitmentType10(Message dataContent);

        /// @brief The function will process the data according to the protocol 11
        /// @param dataContent The transfered data (Client + Data)
        void dataTraitmentType11(Message dataContent);

        /// @brief The function will process the data according to the protocol 12
        /// @param dataContent The transfered data (Client + Data)
        void dataTraitmentType12(Message dataContent);

        /// @brief The function will process the data according to the protocol 13
        /// @param dataContent The transfered data (Client + Data)
        void dataTraitmentType13(Message dataContent);

        /// @brief The function will process the data according to the protocol 14
        /// @param dataContent The transfered data (Client + Data)
        void dataTraitmentType14(Message dataContent);

        /// @brief The function will process the data according to the protocol 15
        /// @param dataContent The transfered data (Client + Data)
        void dataTraitmentType15(Message dataContent);

        /// @brief The function will process the data according to the protocol 16
        /// @param dataContent The transfered data (Client + Data)
        void dataTraitmentType16(Message dataContent);

        /// @brief The function will process the data according to the protocol 17
        /// @param dataContent The transfered data (Client + Data)
        void dataTraitmentType17(Message dataContent);

        /// @brief The function will process the data according to the protocol 20
        /// @param dataContent The transfered data (Client + Data)
        void dataTraitmentType20(Message dataContent);

        /// @brief The function will process the data according to the protocol 21
        /// @param dataContent The transfered data (Client + Data)
        void dataTraitmentType21(Message dataContent);

        /// @brief The function will process the data according to the protocol 30
        /// @param dataContent The transfered data (Client + Data)
        void dataTraitmentType30(Message dataContent);

        /// @brief The function will process the data according to the protocol 31
        /// @param dataContent The transfered data (Client + Data)
        void dataTraitmentType31(Message dataContent);

        /// @brief The function will process the data according to the protocol 40
        /// @param dataContent The transfered data (Client + Data)
        void dataTraitmentType40(Message dataContent);

        /// @brief The function will process the data according to the protocol 41
        /// @param dataContent The transfered data (Client + Data)
        void dataTraitmentType41(Message dataContent);

        /// @brief The function will process the data according to the protocol 42
        /// @param dataContent The transfered data (Client + Data)
        void dataTraitmentType42(Message dataContent);

        /// @brief The function will process the data according to the protocol 50
        /// @param dataContent The transfered data (Client + Data)
        void dataTraitmentType50(Message dataContent);

        /// @brief Bind all data traitment function (Use only in constructor)
        void bindDataTraitmentFunction(void);

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

        /// @brief Map of all the data traitment function. (Type + function)
        std::map<unsigned short, std::function<void(Message)>> _dataTraitment;
    };
} // namespace communicator_lib

#endif /* !RECEIVER_HPP_ */
