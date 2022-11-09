/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** Communicator
*/

/// @file libs/Communicator/Communicator.hpp

#ifndef COMMUNICATOR_HPP_
#define COMMUNICATOR_HPP_

#include <memory>
#include <vector>
#include "Client.hpp"
#include "Database/Database.hpp"
#include "Receiver.hpp"
#include "Sender.hpp"
#include "Transisthor/Transisthor.hpp"

namespace transisthor_lib
{
    class Transisthor;
}

using namespace transisthor_lib;
using namespace database;

namespace communicator_lib
{
    /// @brief Enumeration to know the type of configuration.
    enum roomConfiguration_e {
        PLAYER_NUMBER,
        PLAYER_VELOCITY,
        PLAYER_SHOOT_FREQUENCY,
        ENNEMI_VELOCITY,
        ENNEMI_SHOOT_FREQUENCY,
        TIME_ACCELERATION
    };

    /// @brief Bridge between communicator and server for message
    struct CommunicatorMessage {
        /// @brief The network message
        Message message;
        /// @brief First communication of this client ?
        bool newClient;
    };

    /// @brief Configuration of a room. It contains a name and 6 modifiers.
    struct RoomConfiguration {
        /// @brief Name of the room.
        std::string roomName;
        /// @brief Configuration (6 modifiers).
        /// Use enumerator roomConfiguration_e to set value at the good index.
        short configs[6];
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
        ~Communicator() = default;

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

        /// @brief Ask the sender to send data to a given client
        /// @param client The client's informations
        /// @param data The given data to transfer
        /// @param size Size of the data to transfer (sizeof(data) * quantity)
        /// @param type Data type (Refer to RFC)
        inline void sendDataToAClient(Client &client, void *data, size_t size, unsigned short type)
        {
            _senderModule.sendDataToAClient(client, data, size, type);
        }

        /// @brief Change the bridge destination to a new transisthor
        /// @param transisthorBridge New bridge destination
        inline void setTransisthorBridge(std::shared_ptr<Transisthor> transisthorBridge)
        {
            _transisthorBridge = transisthorBridge;
        }

        /// @brief Get the transisthor bridge
        /// @return The transisthor bridge
        inline std::shared_ptr<Transisthor> getTransisthorBridge(void) { return _transisthorBridge; }

        /// @brief Get the DatabaseApi bridge
        /// @return The databaseApi bridge
        inline Database &getDatabaseApi() { return _databaseApi; };

        /// @brief Cross all client list and return the matched client
        /// @param id matched id
        /// @return founded client
        /// @throw an error when no client his founded, throw a NetworkError
        Client getClientByHisId(unsigned short id);

        /// @brief Function called inside ecs server to know server Endpoint id
        /// @return The server endpoint id
        /// @throw an error when no server can be found (Not in a client communicator), throw a NetworkError
        unsigned short getServerEndpointId(void);

        /// @brief Utilitary function used to send a message with a protocol 50.
        /// @param pseudo The pseudonyme of the author
        /// @param messageContent Content of the message
        /// @param destination of the message
        void utilitarySendChatMessage(
            std::string pseudo, std::string messageContent, std::vector<unsigned short> destination);

        /// @brief Utilitary function used to send a database request with a protocol 40
        /// @param pseudo The wanted client name
        /// @param key The wanted value key
        /// @param destination of the message
        void utilitaryAskForADatabaseValue(
            std::string pseudo, std::string key, std::vector<unsigned short> destination);

        /// @brief Utilitary function used to send a database value with a protocol 41
        /// @param value the database value
        /// @param destination of the message
        void utilitarySendDatabaseValue(std::string value, Client &destination);

        /// @brief Utilitary function used to set a value inside the database with a protocol 42
        /// @param pseudo The wanted client name
        /// @param key The wanted value key
        /// @param value The new value to set
        /// @param destination of the message
        void utilitarySetADatabaseValue(
            std::string pseudo, unsigned short key, std::string value, std::vector<unsigned short> destination);

        /// @brief Utilitary function used to extract a message received by a protocol 50
        /// @param cryptedMessage the crypted message
        /// @return std::vector<std::string> the decrypted pseudo + message
        std::vector<std::string> utilitaryReceiveChatMessage(CommunicatorMessage cryptedMessage);

        /// @brief Utilitary function used to extract a request received by a protocol 40
        /// @param cryptedMessage the crypted message
        /// @return std::vector<std::string> the decrypted pseudo + key
        std::vector<std::string> utilitaryReceiveAskingForDatabaseValue(CommunicatorMessage cryptedMessage);

        /// @brief Utilitary function used to extract the database value received by a protocol 41
        /// @param cryptedMessage the crypted message
        /// @return std::string the value
        std::string utilitaryReceiveDatabaseValue(CommunicatorMessage cryptedMessage);

        /// @brief Utilitary function used to extract the set request received by a protocol 42
        /// @param cryptedMessage the crypted message
        /// @return std::vector<std::string> the decrypted pseudo + type + value
        std::vector<std::string> utilitaryReceiveSetDatabaseValue(CommunicatorMessage cryptedMessage);

        /// @brief Utilitary function used to send a message with a protocol 17.
        /// @param roomName The name of the room configuration.
        /// @param configs Array of modificator used to update some server configuration.
        /// @param newEndPoint The endpoint used to send the configuration.
        void utilitarySendRoomConfiguration(std::string roomName, short *configs, Client newEndpoint);

        /// @brief Utilitary function used to extract a message received by a protocol 17.
        /// @param cryptedMessage The crypted message which contains informations.
        /// @return RoomConfiguration The configuration of the room.
        RoomConfiguration utilitaryReceiveRoomConfiguration(CommunicatorMessage cryptedMessage);

      private:
        /// @brief Send a protocol 20 to a client
        /// @param client The destination
        /// @param newEndpoint The new endpoint to transfer
        void sendProtocol20(Client client, Client newEndpoint);

        /// @brief If the data type is 2X, the function will process the data following the 2X protocol
        /// @param lastMessage The message to trait
        void receiveProtocol2X(Message lastMessage);

        /// @brief If the data type is 3X, the function will process the data following the 3X protocol
        /// @param lastMessage Message to trait
        void receiveProtocol3X(Message lastMessage);

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

        /// @brief Bridge to the transisthor instance
        std::shared_ptr<Transisthor> _transisthorBridge;

        /// @brief Bridge to communicate with the database
        Database _databaseApi;
    };
} // namespace communicator_lib

#endif /* !COMMUNICATOR_HPP_ */
