/*
** EPITECH PROJECT, 2022
** Project
** File description:
** ButtonComponent
*/

#ifndef BUTTONCOMPONENT_HPP_
#define BUTTONCOMPONENT_HPP_

#include "Component/Component.hpp"

namespace ecs
{
    /// @brief The Button Component, used to make the difference between the component
    class Button : public Component {
      public:
        /// @brief If the component is hovered, the value will be set to true
        bool IsHovered;
        /// @brief If the component is clicked, the value will be set to true
        bool IsClicked;

        /// @brief Constructor of the Button Component
        /// @param hovered true if the component will be hovered at first, false otherwise
        /// @param clicked true if the component will be clicked at first, false otherwise
        Button(bool hovered, bool clicked) : IsHovered(hovered), IsClicked(clicked) {};
        /// @brief Copy Constructor of the Button Component
        /// @param old The copy of the Button Component
        Button(const Button &old) : IsHovered(old.IsHovered), IsClicked(old.IsClicked) {};
        /// @brief Default Destructor
        ~Button() = default;
    };
} // namespace ecs

#endif /* !BUTTONCOMPONENT_HPP_ */
