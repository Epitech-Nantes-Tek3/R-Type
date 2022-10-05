/*
** EPITECH PROJECT, 2022
** Project
** File description:
** ShootingFrequencyComponent
*/

#ifndef SHOOTINGFREQUENCYCOMPONENT_HPP_
#define SHOOTINGFREQUENCYCOMPONENT_HPP_

#include "Component.hpp"
#include <chrono>

using namespace std::chrono;

namespace ecs
{
    /// @brief The ShootingFrequency class, how many seconds will be between two projectiles
    class ShootingFrequency : public Component{
      public:
        /// @brief The delay between two shoots
        duration<double> frequency;

        /// @brief Constructor of the ShootingFrequency Component
        /// @param newfrequency the shooting's delay
        ShootingFrequency(duration<double> newFrequency) : frequency(newFrequency) {};
        /// @brief Copy Constructor of the ShootingFrequency Component
        /// @param old the copy of the ShootingFrequency Component
        ShootingFrequency(const ShootingFrequency &old) : frequency(old.frequency) {};
        /// @brief Default Destructor
        ~ShootingFrequency() = default;
    };
} // namespace ecs

#endif /* !SHOOTINGFREQUENCYCOMPONENT_HPP_ */
