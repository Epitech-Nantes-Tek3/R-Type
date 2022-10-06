/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** ControllerInputComponent
*/

#ifndef CONTROLLERINPUTCOMPONENT_HPP_
#define CONTROLLERINPUTCOMPONENT_HPP_

#include "Component.hpp"
#include <SFML/Graphics.hpp>
#include <unordered_map>

namespace ecs {
    enum action_e;
    class ControllerInputComponent {
        public:
            std::unordered_map<sf::Event::JoystickButtonEvent, std::pair<ecs::action_e, ecs::action_e>> controllerMapActions;
            ControllerInputComponent();
            ~ControllerInputComponent();
    };
}

#endif /* !CONTROLLERINPUTCOMPONENT_HPP_ */
