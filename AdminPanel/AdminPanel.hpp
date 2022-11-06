/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** AdminPanel
*/

#ifndef ADMINPANEL_HPP_
#define ADMINPANEL_HPP_

#include "Communicator/Communicator.hpp"

using namespace communicator_lib;

namespace admin_panel
{
    /// @brief The global Admin panel class. Use for interact with the database.
    class AdminPanel {
      public:

        /// @brief A basic struct representing a panel command
        typedef struct panelCommandS {
            /// @brief The command keyword
            std::string keyWord;
            /// @brief The targeted user
            std::string userName;
            /// @brief List of all additional option
            std::vector<std::string> options;
        } panelCommandT;

        /// @brief Construct a new AdminPanel object
        /// @param address Ip address of the admin panel
        /// @param port Listening port for network process
        /// @param serverAddress server address
        /// @param serverPort room port
        AdminPanel(std::string address = "127.0.0.1", unsigned short port = 0, std::string serverAddress = "127.0.0.1",
            unsigned short serverPort = 0);

        /// @brief Destroy the Admin Panel object
        ~AdminPanel() = default;

        /// @brief Start the admin panel global loop
        void startLoop();

      private:
        /// @brief Network informations of the Room.
        Client _networkInformations;

        /// @brief Instance of the communicator library
        std::shared_ptr<Communicator> _communicatorInstance;

        /// @brief Tell if the AdminPanel is waiting for a Database response
        bool _waitingForAnswer;

        /// @brief Tell if the AdminPanel is authentified.
        bool _isAuth;

        /// @brief Network informations of the server
        Client _serverEndpoint;

        /// @brief Name of the connected client
        std::string _pseudo;

        /// @brief Current panel state. True for running and False for ended.
        bool _state;

        /// @brief Start the authentification process
        void _authentificationProcess();

        /// @brief Handle a received data from a protocol 41.
        /// @param databaseAnswer The received data
        void _handleAReceivedData(CommunicatorMessage databaseAnswer);

        /// @brief Ask the user for a new request
        void _getARequest();
    };
} // namespace admin_panel

#endif /* !ADMINPANEL_HPP_ */
