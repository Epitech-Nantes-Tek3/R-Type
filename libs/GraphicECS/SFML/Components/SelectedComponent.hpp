/*
** EPITECH PROJECT, 2022
** Project
** File description:
** SelectedComponent
*/

#ifndef SELECTEDCOMPONENT_HPP_
#define SELECTEDCOMPONENT_HPP_

#include "Component/Component.hpp"

namespace graphicECS::SFML::Components
{
    /// @brief This component class permit to know if a writable entity is selected
    class Selected : public ecs::Component {};
} // namespace graphicECS::SFML::Components

#endif /* !SELECTEDCOMPONENT_HPP_ */