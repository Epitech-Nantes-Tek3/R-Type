/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** Controllable
*/

#pragma once

#include "Component/Component.hpp"

namespace ecs
{
    /// @brief A Component which is used to know which Entity the player control
    class Controllable : public Component {
      public:
        ///@brief Construct a new Controllable object
        Controllable();

        ///@brief Destroy the Controllable object
        ~Controllable();
    };
} // namespace ecs
