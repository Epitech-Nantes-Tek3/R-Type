/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** ControllerButtonInputComponent
*/

#ifndef CONTROLLERBUTTONINPUTCOMPONENT_HPP_
#define CONTROLLERBUTTONINPUTCOMPONENT_HPP_

#include <functional>
#include "Component/Component.hpp"
#include "World/World.hpp"
#include <unordered_map>

namespace graphicECS::SFML::Components
{
    /// @brief This component class stores an unsorted map of action/value pair.
    /// This class is created in order to find an action depending on a controller button input.
    /// It inherites from Component.
    class ControllerButtonInputComponent : public ecs::Component {
      public:
        /// @brief This unordered_map links SFML controller button input to an action/value pair enum.
        std::unordered_map<unsigned int, std::function<void(ecs::World &, float)>> controllerButtonMapActions;

        /// @brief Default constructor of the class.
        ControllerButtonInputComponent() = default;

        /// @brief Default destructor of the class.
        ~ControllerButtonInputComponent() = default;
    };
} // namespace graphicECS::SFML::Components

#endif /* !CONTROLLERButtonINPUTCOMPONENT_HPP_ */
