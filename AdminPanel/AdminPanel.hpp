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

        /// @brief Construct a new AdminPanel object
        /// @param address Ip address of the admin panel
        /// @param port Listening port for network process
        AdminPanel(std::string address = "127.0.0.1", unsigned short port = 0);

        ~AdminPanel() = default;

        /// @brief Start the admin panel global loop
        void startLoop();

      private:
        /// @brief Network informations of the Room.
        Client _networkInformations;

        /// @brief Instance of the communicator library
        std::shared_ptr<Communicator> _communicatorInstance;
    };
} // namespace admin_panel

#endif /* !ADMINPANEL_HPP_ */
