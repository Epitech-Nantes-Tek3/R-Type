/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** ControllerJoystickInputComponent
*/

#ifndef CONTROLLERJOYSTICKINPUTCOMPONENT_HPP_
#define CONTROLLERJOYSTICKINPUTCOMPONENT_HPP_

#include <SFML/Graphics.hpp>
#include "Component/Component.hpp"
#include <unordered_map>
#include <functional>

namespace ecs
{
    /// @brief This component class stores an unsorted map of action/value pair.
    /// This class is created in order to find an action depending on a controller joystick input.
    /// It inherites from Component.
    class ControllerJoystickInputComponent : public Component {
        public:
            /// @brief This unordered_map links SFML controller joystick input to an action/value pair enum.
            std::unordered_map<unsigned int, std::pair<std::function<void()>, float>> controllerJoystickMapActions;

            /// @brief Constructor of the class.
            ControllerJoystickInputComponent() = default;

            /// @brief Default destructor of the class.
            ~ControllerJoystickInputComponent() = default;
    };
} // namespace ecs

#endif /* !CONTROLLERJOYSTICKINPUTCOMPONENT_HPP_ */
