/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** InvinsibleComponent
*/

#ifndef INVINSIBLECOMPONENT_HPP_
#define INVINSIBLECOMPONENT_HPP_

#include "Component/Component.hpp"

namespace ecs
{
    /// @brief The Invinsible component, to nullify all damages
    /// It's a networkable component.
    class Invinsible : public Component {
      public:
        /// @brief The network status of the component. True if it has been modified since it was last sent.
        bool modified;

        /// @brief If the server need to resend it to everyone
        bool sendToEveryone;

        /// @brief Id of the client to delete from the Database after sending the death component. 0 if no client needed to be deleted
        unsigned short clientToDelete;

        ///@brief Construct a new Invinsible object
        Invinsible() : modified(false), sendToEveryone(false), clientToDelete(0){};
        ///@brief Destroy the Invinsible object
        ~Invinsible() = default;
    };
} // namespace ecs

#endif /* !INVINSIBLECOMPONENT_HPP_ */
