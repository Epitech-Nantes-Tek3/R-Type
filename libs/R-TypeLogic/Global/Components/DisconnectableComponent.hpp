/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** DisconnectableComponent
*/

#ifndef DISCONNECTABLECOMPONENT_HPP_
#define DISCONNECTABLECOMPONENT_HPP_

#include "Component/Component.hpp"

namespace ecs
{
    /// @brief The Disconnectable class, defining if an entity is affected by a deconnection process
    class Disconnectable : public Component {};
} // namespace ecs

#endif /* !DISCONNECTABLECOMPONENT_HPP_ */
