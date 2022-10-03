/*
** EPITECH PROJECT, 2022
** Project
** File description:
** VelocityComponent
*/

#ifndef VELOCITYCOMPONENT_HPP_
#define VELOCITYCOMPONENT_HPP_

#include "Component.hpp"

namespace ecs
{
    /// @brief The velocity class, multiplying the movement of the entity
    class Velocity : public Component{
      public:
        /// @brief The multiplier of the movement
        double multiplier;

        /// @brief Constructor of the Velocity Component
        /// @param newMultiplier the movement's multiplier
        Velocity(double newMultiplier) : multiplier(newMultiplier) {};
        /// @brief Copy Constructor of the Velocity Component
        /// @param old the copy of the Velocity Component
        Velocity(const Velocity &old) : multiplier(old.multiplier) {};
        /// @brief Default Destructor
        ~Velocity() = default;
    };
} // namespace ecs

#endif /* !VELOCITYCOMPONENT_HPP_ */
