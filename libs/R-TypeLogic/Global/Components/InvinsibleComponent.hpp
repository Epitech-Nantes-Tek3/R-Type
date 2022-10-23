/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** InvinsibleComponent
*/

#ifndef INVINSIBLECOMPONENT_HPP_
#define INVINSIBLECOMPONENT_HPP_

#include "Component/Component.hpp"

namespace rtypelogic::global
{
    /// @brief The Invinsible component, to nullify all damages
    /// It's a networkable component.
    class Invinsible : public ecs::Component {
      public:
        /// @brief The network status of the component. True if it has been modified since it was last sent.
        bool modified;

        /// @brief If the server need to resend it to everyone
        bool sendToEveryone;

        ///@brief Construct a new Invinsible object
        Invinsible() : modified(false), sendToEveryone(false){};
        ///@brief Destroy the Invinsible object
        ~Invinsible() = default;
    };
} // namespace rtypelogic::global

#endif /* !INVINSIBLECOMPONENT_HPP_ */
