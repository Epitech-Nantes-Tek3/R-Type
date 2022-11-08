/*
** EPITECH PROJECT, 2022
** R-Type [WSL : Ubuntu]
** File description:
** InputDelayComponent
*/

#ifndef INPUTDELAYCOMPONENT_HPP_
#define INPUTDELAYCOMPONENT_HPP_

#include <chrono>
#include "Component/Component.hpp"

namespace graphicECS::SFML::Components
{
    /// @brief This component stores a velocity modificator and use it just before the sending
    class InputDelayComponent : public ecs::Component {
      public:
        /// @brief The multiplier of the abscissa movement (between 0.1 and 10)
        double multiplierAbscissa;

        /// @brief The multiplier of the ordinate movement (between 0.1 and 10)
        double multiplierOrdinate;

        /// @brief Construct the class to set default values.
        /// @param newMultiplierX the movement's multiplier of abscissa
        /// @param newMultiplierY the movement's multiplier of ordinate
        InputDelayComponent(double newMultiplierX = 0, double newMultiplierY = 0)
            : multiplierAbscissa(newMultiplierX), multiplierOrdinate(newMultiplierY){};

        /// @brief Default destructor.
        ~InputDelayComponent() = default;
    };
} // namespace graphicECS::SFML::Components

#endif /* !INPUTDELAYCOMPONENT_HPP_ */
