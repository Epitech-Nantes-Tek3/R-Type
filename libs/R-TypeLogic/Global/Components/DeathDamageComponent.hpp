/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** DeathDamageComponent
*/

#ifndef DEATHDAMAGECOMPONENT_HPP_
#define DEATHDAMAGECOMPONENT_HPP_

#include "Component/Component.hpp"

namespace rtypelogic::global
{
    /// @brief The DeathDamage class, inflicting damage after the owner's death
    class DeathDamage : public ecs::Component {
      public:
        /// @brief The number of DeathDamage, to be substract to the Life Point
        unsigned short deathDamagePoint;

        /// @brief Constructor of the DeathDamage Component
        /// @param newDeathDamage the number of DeathDamage
        DeathDamage(unsigned short newDeathDamage = 0) : deathDamagePoint(newDeathDamage){};
        /// @brief Default Destructor
        ~DeathDamage() = default;
    };
} // namespace rtypelogic::global

#endif /* !DEATHDAMAGECOMPONENT_HPP_ */
