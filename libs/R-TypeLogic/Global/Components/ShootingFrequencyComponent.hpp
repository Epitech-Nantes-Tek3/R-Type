/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** ShootingFrequencyComponent
*/

#ifndef SHOOTINGFREQUENCYCOMPONENT_HPP_
#define SHOOTINGFREQUENCYCOMPONENT_HPP_

#include <chrono>
#include "Component/Component.hpp"

using namespace std::chrono;

namespace ecs
{
    /// @brief The ShootingFrequency class, how many seconds will be between two projectiles
    class ShootingFrequency : public Component {
      public:
        /// @brief The delay between two shoots
        duration<double> frequency;

        /// @brief The base delay, only used to reset the frequency value
        const duration<double> baseFrequency;

        /// @brief Constructor of the ShootingFrequency Component
        /// @param newfrequency the shooting's delay
        ShootingFrequency(duration<double> newFrequency) : frequency(newFrequency), baseFrequency(frequency){};
        /// @brief Default Constructor of the ShootingFrequency Component
        /// @param newfrequency the shooting's delay
        ShootingFrequency(double newFrequency = 0.0) : frequency(duration<double>(newFrequency)), baseFrequency(frequency){};
        /// @brief Default Destructor
        ~ShootingFrequency() = default;
    };
} // namespace ecs

#endif /* !SHOOTINGFREQUENCYCOMPONENT_HPP_ */
