/*
** EPITECH PROJECT, 2022
** Project
** File description:
** VelocityComponent
*/

#ifndef VELOCITYCOMPONENT_HPP_
#define VELOCITYCOMPONENT_HPP_

#include "Component/Component.hpp"

namespace ecs
{
    /// @brief The velocity class, multiplying the movement of the entity
    class Velocity : public Component{
      public:
        /// @brief The multiplier of the abscissa movement (between 0.1 and 10)
        double multiplierAbscissa;
        /// @brief The multiplier of the ordinate movement (between 0.1 and 10)
        double multiplierOrdinate;

        /// @brief Constructor of the Velocity Component
        /// @param newMultiplierX the movement's multiplier of abscissa
        /// @param newMultiplierY the movement's multiplier of ordinate
        Velocity(double newMultiplierX = 0, double newMultiplierY = 0) : multiplierAbscissa(newMultiplierX), multiplierOrdinate(newMultiplierY) {};
        /// @brief Default Destructor
        ~Velocity() = default;
    };
} // namespace ecs

#endif /* !VELOCITYCOMPONENT_HPP_ */
