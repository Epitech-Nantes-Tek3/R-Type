/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** Controllable
*/

#pragma once

#include "Component/Component.hpp"

namespace transisthor::ecslogic
{
    /// @brief A Component which is used to know which Entity the player control
    class Controllable : public ecs::Component {};
} // namespace transisthor::ecslogic
