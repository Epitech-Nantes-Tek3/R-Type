/*
** EPITECH PROJECT, 2022
** Project
** File description:
** DeathDamageComponent
*/

#ifndef DEATHDAMAGECOMPONENT_HPP_
#define DEATHDAMAGECOMPONENT_HPP_

#include "Component.hpp"

namespace ecs
{
    /// @brief The DeathDamage class, inflicting damage after the owner's death
    class DeathDamage : public Component{
      public:
        /// @brief The number of DeathDamage, to be substract to the Life Point
        unsigned short deathDamagePoint;

        /// @brief Constructor of the DeathDamage Component
        /// @param newDeathDamage the number of DeathDamage
        DeathDamage(unsigned short newDeathDamage) : deathDamagePoint(newDeathDamage) {};
        /// @brief Copy Constructor of the DeathDamage Component
        /// @param old the copy of the DeathDamage component
        DeathDamage(const DeathDamage &old) : deathDamagePoint(old.deathDamagePoint) {};
        /// @brief Default Destructor
        ~DeathDamage() = default;
    };
} // namespace ecs

#endif /* !DEATHDAMAGECOMPONENT_HPP_ */
