/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** DeathComponent
*/

#ifndef DEATHCOMPONENT_HPP_
#define DEATHCOMPONENT_HPP_

#include "Component/Component.hpp"

namespace ecs
{
    /// @brief The Death Component which defines that an entity is dead and will be deleted by Death System
    /// It's a networkable component.
    class Death : public Component {
      public:
        /// @brief The network status of the component. True if it has been modified since it was last sent.
        bool modified;

        /// @brief If the server need to resend it to everyone
        bool sendToEveryone;

        /// @brief Id of the client to delete from the Database after sending the death component. 1000 if no client
        /// needed to be deleted
        unsigned short clientToDelete;

        ///@brief Construct a new Death object
        Death() : modified(true), sendToEveryone(false), clientToDelete(1000){};
        ///@brief Destroy the Death object
        ~Death() = default;
    };
} // namespace ecs

#endif /* !DEATHCOMPONENT_HPP_ */
