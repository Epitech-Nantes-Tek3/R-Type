/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** UserConnection
*/

#ifndef USERCONNECTION_HPP_
#define USERCONNECTION_HPP_

#include "World/World.hpp"

namespace client_data
{
    /// @brief This class is used to get a pseudo and a password in a GUI to log in a client.
    class UserConnection {
      public:
        /// @brief Constructor of UserConnection class.
        UserConnection();

        /// @brief Destructor of UserConnection class.
        ~UserConnection();

        /// @brief Launch a user connection GUI.
        void userConnection();

      private:
        /// @brief Init all shared resources of the world.
        void _loadResourcesUserConnection();

        /// @brief Init all systems of the world.
        void _loadSystemsUserConnection();

        /// @brief Init some entities only created by the client.
        /// @param buttonSendId The id of the button send.
        /// @param buttonPseudoId The id of the button pseudo.
        /// @param buttonPasswordId The id of the button password.
        void _loadEntitiesUserConnection(
            std::size_t &buttonSendId, std::size_t &buttonPseudoId, std::size_t &buttonPasswordId);

        /// @brief Set inputs of the user connection GUI.
        /// @param entity The entity to set.
        void _setInputUserConnection(ecs::Entity &entity);

        /// @brief Run the user connection GUI.
        /// @param buttonSendId The id of the button send.
        void _runSystemsUserConnection(std::size_t buttonSendId);

        /// @brief The world of the user connection GUI.
        std::shared_ptr<ecs::World> _world;

        /// @brief The pseudo of the user.
        std::string _pseudo;

        /// @brief The password of the user.
        std::string _password;
    };
} // namespace client_data

#endif /* !USERCONNECTION_HPP_ */
