/*
** EPITECH PROJECT, 2022
** Project
** File description:
** ControlableComponent
*/

#ifndef CONTROLABLECOMPONENT_HPP_
#define CONTROLABLECOMPONENT_HPP_

#include "Component/Component.hpp"

namespace ecs
{
    /// @brief The controlable class, defining if an entity is affected by the player's input
    class Controlable : public Component {};
} // namespace ecs

#endif /* !CONTROLABLECOMPONENT_HPP_ */
