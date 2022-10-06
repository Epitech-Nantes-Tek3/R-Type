/*
** EPITECH PROJECT, 2022
** Project
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
        ChargedAttack(duration<double> newRechargingTime) : rechargingTime(newRechargingTime) {};
        /// @brief Copy Constructor of ChargedAttack Component
        /// @param old the copy of the ChargeAttack Component
        ChargedAttack(const ChargedAttack &old) : rechargingTime(old.rechargingTime) {};
        /// @brief Default Destructor
        ~ChargedAttack() = default;

    };
} // namespace ecs

#endif /* !CHARGEDATTACK_HPP_ */
