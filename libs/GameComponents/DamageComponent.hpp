/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** DamageComponent
*/

#ifndef DAMAGECOMPONENT_HPP_
#define DAMAGECOMPONENT_HPP_

#include "Component/Component.hpp"

namespace ecs
{
    /// @brief The Damage class, reducing the entity's life
    class Damage : public Component {
      public:
        /// @brief The number of damage, to be substract to the Life Point
        unsigned short damagePoint;

        /// @brief Constructor of the Damage Component
        /// @param newDamage the number of damage
        Damage(unsigned short newDamage = 0) : damagePoint(newDamage){};
        /// @brief Default Destructor
        ~Damage() = default;
    };
} // namespace ecs

#endif /* !DAMAGECOMPONENT_HPP_ */
