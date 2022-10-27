/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** InvisibleComponent
*/

#ifndef INVISIBLECOMPONENT_HPP_
#define INVISIBLECOMPONENT_HPP_

#include "Component/Component.hpp"

namespace ecs
{
    /// @brief The Invisible component, to make an entity lives without drawing it
    /// It's a networkable component.
    class Invisible : public Component {
      public:
        /// @brief The network status of the component. True if it has been modified since it was last sent.
        bool modified;

        /// @brief If the server need to resend it to everyone
        bool sendToEveryone;

        /// @brief Id of the client to delete from the Database after sending the death component. 0 if no client needed to be deleted
        unsigned short clientToDelete;

        ///@brief Construct a new Invisible object
        Invisible() : modified(false), sendToEveryone(false), clientToDelete(0){};
        ///@brief Destroy the Invisible object
        ~Invisible() = default;
    };
} // namespace ecs

#endif /* !INVISIBLECOMPONENT_HPP_ */
