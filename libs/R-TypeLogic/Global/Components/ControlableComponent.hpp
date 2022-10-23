/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** ControlableComponent
*/

#ifndef CONTROLABLECOMPONENT_HPP_
#define CONTROLABLECOMPONENT_HPP_

#include "Component/Component.hpp"

namespace rtypelogic::global
{
    /// @brief The controlable class, defining if an entity is affected by the player's input
    class Controlable : public ecs::Component {};
} // namespace rtypelogic::global

#endif /* !CONTROLABLECOMPONENT_HPP_ */
