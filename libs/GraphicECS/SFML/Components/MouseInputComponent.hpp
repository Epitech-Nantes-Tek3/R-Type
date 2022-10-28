/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** MouseInputComponent
*/

#ifndef MOUSEINPUTCOMPONENT_HPP_
#define MOUSEINPUTCOMPONENT_HPP_

#include <SFML/Graphics.hpp>
#include <functional>
#include "Component/Component.hpp"
#include "World/World.hpp"
#include <unordered_map>

namespace graphicECS::SFML::Components
{
    /// @brief This component class stores an unsorted map of action/value pair.
    /// This class is created in order to find an action depending on a mouse button pressed or released.
    /// It inherits from Component.
    class MouseInputComponent : public ecs::Component {
      public:
        /// @brief This unordered map links SFML mouse button input to an action/float pair enum.
        std::unordered_map<sf::Mouse::Button, std::pair<ActionQueueComponent::inputAction_e, float>> MouseMapActions;

        /// @brief Constructor of the class.
        MouseInputComponent() = default;

        /// @brief Default destructor of the class.
        ~MouseInputComponent() = default;
    };
} // namespace graphicECS::SFML::Components

#endif /* !MOUSEINPUTCOMPONENT_HPP_ */
