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
        DamageRadius(unsigned short newRadius = 0) : radius(newRadius) {};
        /// @brief Default Destructor
        ~DamageRadius() = default;
    };
} // namespace ecs

#endif /* !DAMAGERADIUSCOMPONENT_HPP_ */
