/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** ChargedAttack
*/

#ifndef CHARGEDATTACK_HPP_
#define CHARGEDATTACK_HPP_

#include "Component/Component.hpp"
#include <chrono>

using namespace std::chrono;

namespace ecs
{
    /// @brief The Charged attack class, adding a cooldown before making huge damage
    class ChargedAttack : public Component {
      public:
        /// @brief Time before making a charged attack, will be refreshed by a system
        duration<double> rechargingTime;

        /// @brief Constructor of the ChargedAttack Component
        /// @param newRechargingTime Time before making a charged attack
        ChargedAttack(duration<double> newRechargingTime = duration<double>(0)) : rechargingTime(newRechargingTime) {};
        /// @brief Default Destructor
        ~ChargedAttack() = default;

    };
} // namespace ecs

#endif /* !CHARGEDATTACK_HPP_ */
