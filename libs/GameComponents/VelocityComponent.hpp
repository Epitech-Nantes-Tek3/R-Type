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
        Velocity(double newMultiplierX, double newMultiplierY) : multiplierAbscissa(newMultiplierX), multiplierOrdinate(newMultiplierY) {};
        /// @brief Copy Constructor of the Velocity Component
        /// @param old the copy of the Velocity Component
        Velocity(const Velocity &old) : multiplierAbscissa(old.multiplierAbscissa), multiplierOrdinate(old.multiplierOrdinate) {};
        /// @brief Default Destructor
        ~Velocity() = default;
    };
} // namespace ecs

#endif /* !VELOCITYCOMPONENT_HPP_ */
