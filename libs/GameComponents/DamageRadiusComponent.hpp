/*
** EPITECH PROJECT, 2022
** Project
** File description:
** DamageRadiusComponent
*/

#ifndef DAMAGERADIUSCOMPONENT_HPP_
#define DAMAGERADIUSCOMPONENT_HPP_

#include "Component/Component.hpp"

namespace ecs
{
    /// @brief The Damage Radius class, defining the damage zone
    class DamageRadius : public Component{
      public:
        /// @brief The range of the projectile's explosion
        unsigned short radius;

        /// @brief Constructor of the DamageRadius Component
        /// @param newRadius the new radius
        DamageRadius(unsigned short newRadius) : radius(newRadius) {};
        /// @brief Copy Constructor of the DamageRadius Component
        /// @param old the copy of the DamageRadius component
        DamageRadius(const DamageRadius &old) : radius(old.radius) {};
        /// @brief Default Destructor
        ~DamageRadius() = default;
    };
} // namespace ecs

#endif /* !DAMAGERADIUSCOMPONENT_HPP_ */
