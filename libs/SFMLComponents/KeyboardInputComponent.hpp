/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** KeyboardInputComponent
*/

#ifndef KEYBOARDINPUTCOMPONENT_HPP_
#define KEYBOARDINPUTCOMPONENT_HPP_

#include "Component/Component.hpp"
#include <SFML/Graphics.hpp>
#include <unordered_map>

namespace ecs
{
    /// @brief Definition of the enum action_e.
    enum action_e
    {
        NONE
    };

    /// @brief This component class stores an unsorted map of action/value pair.
    /// This class is created in order to find an action depending on a key pressed or released.
    /// It inherits from Component.
    class KeyboardInputComponent : public Component {
        public:
            /// @brief This unordered_map links SFML key input to an action/value pair enum.
            std::unordered_map<sf::Keyboard::Key, std::pair<ecs::action_e, float>> keyboardMapActions;

            /// @brief Constructor of the class.
            KeyboardInputComponent() = default;

            /// @brief Default destructor of the class.
            ~KeyboardInputComponent() = default;
    };
} // namespace ecs

#endif /* !KEYBOARDINPUTCOMPONENT_HPP_ */
