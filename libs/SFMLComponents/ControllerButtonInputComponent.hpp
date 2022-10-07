/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** ControllerButtonInputComponent
*/

#ifndef CONTROLLERBUTTONINPUTCOMPONENT_HPP_
#define CONTROLLERBUTTONINPUTCOMPONENT_HPP_

#include "Component/Component.hpp"
#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <ECSActions.hpp>
#include <functional>

namespace ecs
{
    /// @brief This component class stores an unsorted map of action/value pair.
    /// This class is created in order to find an action depending on a controller button input.
    /// It inherites from Component.
    class ControllerButtonInputComponent : public Component {
        public:
            /// @brief This unordered_map links SFML controller button input to an action/value pair enum.
            std::unordered_map<unsigned int, std::pair<std::function<void()>, float>> controllerButtonMapActions;

            /// @brief Constructor of the class.
            ControllerButtonInputComponent() = default;

            /// @brief Default destructor of the class.
            ~ControllerButtonInputComponent() = default;
    };
} // namespace ecs

#endif /* !CONTROLLERButtonINPUTCOMPONENT_HPP_ */
