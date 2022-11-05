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
    class UserConnection {
      public:
        UserConnection();
        ~UserConnection();
        void userConnection();

      private:
        void _loadResourcesUserConnection();
        void _loadSystemsUserConnection();
        void _loadEntitiesUserConnection(std::size_t &buttonSendId, std::size_t &buttonPseudoId, std::size_t &buttonPasswordId);
        void _setInputUserConnection(ecs::Entity &entity);
        void _runSystemsUserConnection(std::size_t buttonSendId);
        ecs::World _world;
    };
} // namespace client_data

#endif /* !USERCONNECTION_HPP_ */
