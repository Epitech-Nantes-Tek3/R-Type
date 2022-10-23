/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** InvisibleComponent
*/

#ifndef INVISIBLECOMPONENT_HPP_
#define INVISIBLECOMPONENT_HPP_

#include "Component/Component.hpp"

namespace rtypelogic::global
{
    /// @brief The Invisible component, to make an entity lives without drawing it
    /// It's a networkable component.
    class Invisible : public ecs::Component {
      public:
        /// @brief The network status of the component. True if it has been modified since it was last sent.
        bool modified;

        /// @brief If the server need to resend it to everyone
        bool sendToEveryone;

        ///@brief Construct a new Invisible object
        Invisible() : modified(false), sendToEveryone(){};
        ///@brief Destroy the Invisible object
        ~Invisible() = default;
    };
} // namespace rtypelogic::global

#endif /* !INVISIBLECOMPONENT_HPP_ */
