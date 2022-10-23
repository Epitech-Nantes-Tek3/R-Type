/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** ButtonComponent
*/

#ifndef BUTTONCOMPONENT_HPP_
#define BUTTONCOMPONENT_HPP_

#include "Component/Component.hpp"

namespace rtypelogic::global
{
    /// @brief The Button Component, used to make the difference between the component
    class Button : public ecs::Component {
      public:
        /// @brief If the component is hovered, the value will be set to true
        bool IsHovered;
        /// @brief If the component is clicked, the value will be set to true
        bool IsClicked;

        /// @brief Constructor of the Button Component
        /// @param hovered true if the component will be hovered at first, false otherwise
        /// @param clicked true if the component will be clicked at first, false otherwise
        Button(bool hovered = true, bool clicked = true) : IsHovered(hovered), IsClicked(clicked){};
        /// @brief Default Destructor
        ~Button() = default;
    };
} // namespace rtypelogic::global

#endif /* !BUTTONCOMPONENT_HPP_ */
