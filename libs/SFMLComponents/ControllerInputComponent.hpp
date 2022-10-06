/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** ControllerInputComponent
*/

#ifndef CONTROLLERINPUTCOMPONENT_HPP_
#define CONTROLLERINPUTCOMPONENT_HPP_

#include "Component/Component.hpp"
#include <SFML/Graphics.hpp>
#include <unordered_map>

namespace ecs {
    /// @brief Definition of the enum action_e.
    enum action_e;

    /// @brief This component class stores an unsorted map of action/value pair.
    /// This class is created in order to find an action depending on a controller input pressed or released.
    /// It inherites from Component.
    class ControllerInputComponent : public Component {
        public:
            /// @brief Enumeration of controller's events.
            enum controllerInputE
            {
                UNDEFINE,
                BUTTON_1,
                BUTTON_2,
                BUTTON_3,
                BUTTON_4,
                DIRECTION_1,
                DIRECTION_2,
                DIRECTION_3,
                DIRECTION_4,
                JOY_1_1,
                JOY_1_2,
                JOY_1_3,
                JOY_1_4,
                JOY_1_5,
                JOY_2_1,
                JOY_2_2,
                JOY_2_3,
                JOY_2_4,
                JOY_2_5,
                OPTION,
                SHARE,
                HOME,
                BACK_RIGHT_1,
                BACK_RIGHT_2,
                BACK_LEFT_1,
                BACK_LEFT_2
            };

            /// @brief This unordered_map links SFML
            std::unordered_map<controllerInputE, std::pair<ecs::action_e, float>> controllerMapActions;

            /// @brief Constructor of the class.
            ControllerInputComponent();

            /// @brief Default destructor of the class.
            ~ControllerInputComponent() = default;
    };
}

#endif /* !CONTROLLERINPUTCOMPONENT_HPP_ */
