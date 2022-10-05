/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** KeyboardInputComponent
*/

#ifndef KEYBOARDINPUTCOMPONENT_HPP_
#define KEYBOARDINPUTCOMPONENT_HPP_

#include "Component.hpp"
#include <SFML/Graphics.hpp>
#include <unordered_map>

namespace ecs
{
    enum action_e;
    class KeyboardInputComponent : public Component {
        public:
            std::unordered_map<sf::Keyboard::Key, std::pair<ecs::action_e, ecs::action_e>> keyboardMapActions;
            KeyboardInputComponent();
            ~KeyboardInputComponent() = default;
    };
}

#endif /* !KEYBOARDINPUTCOMPONENT_HPP_ */
