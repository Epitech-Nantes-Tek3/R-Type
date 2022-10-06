/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** Component
*/

#pragma once
#include <cstring>

namespace ecs
{
    /// @brief This is the Component Class for ECS
    /// The base component type, all components must inherit from Component.
    class Component {
      public:
        /// @brief This is the default destructor of Component Class
        ~Component() = default;

      protected:
        /// @brief This is the constructor of Component Class
        /// Because it can be use only by things that heritate by it
        Component() = default;
    };

    /// @brief Create a component from his byte form
    /// @tparam C Type of the component
    /// @param byteCode Byte value of the component
    /// @return C The newly created comoponent
    template <std::derived_from<Component> C> C buildComponentFromByteCode(void *byteCode)
    {
        C convertedComponent;

        std::memcpy(&convertedComponent, byteCode, sizeof(C));
        return convertedComponent;
    }
} // namespace ecs
