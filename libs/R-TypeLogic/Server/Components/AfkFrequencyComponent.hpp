/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** AfkFrequencyComponent
*/

#ifndef AFKFREQUENCYCOMPONENT_HPP_
#define AFKFREQUENCYCOMPONENT_HPP_

#include <chrono>
#include "Component/Component.hpp"

using namespace std::chrono;

namespace ecs
{
    /// @brief The AfkFrequency class, how many seconds will pass before the entity will be consided has inactive
    class AfkFrequency : public Component {
      public:
        /// @brief The delay before inactivity detection
        duration<double> frequency;

        /// @brief The base delay, only used to reset the frequency value
        const duration<double> baseFrequency;

        /// @brief Constructor of the AfkFrequency Component
        /// @param newfrequency the afk's delay
        AfkFrequency(duration<double> newFrequency) : frequency(newFrequency), baseFrequency(frequency){};
        /// @brief Default Constructor of the AfkFrequency Component
        /// @param newfrequency the afk's delay
        AfkFrequency(double newFrequency = 0.0) : frequency(duration<double>(newFrequency)), baseFrequency(frequency){};
        /// @brief Default Destructor
        ~AfkFrequency() = default;
    };
} // namespace ecs

#endif /* !AFKFREQUENCYCOMPONENT_HPP_ */
