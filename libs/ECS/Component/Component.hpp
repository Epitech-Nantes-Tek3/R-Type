/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** Component
*/

#pragma once

namespace ecs
{
    /// @brief This is the Component Class for ECS
    /// The base component type, all components must inherit from Component.
    class Component {
      public:
        /// @brief This is the destructor of Component Class
        virtual ~Component() = default;

      protected:
        /// @brief This is the constructor of Component Class
        /// Because it can be use only by things that eritate by it
        virtual Component() = default;
    };
} // namespace ecs
