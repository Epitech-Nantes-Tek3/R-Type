/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** AlliedProjectileComponent
*/

#ifndef PROJECTILEALLYCOMPONENT_HPP_
#define PROJECTILEALLYCOMPONENT_HPP_

#include "Component/Component.hpp"

namespace rtypelogic::global
{
    /// @brief Allied Projectile Component allows an entity to be used as an Allied Projectile
    class AlliedProjectile : public ecs::Component {
      public:
        /// @brief Network id of the parent
        unsigned short parentNetworkId;

        /// @brief Construct a new AlliedProjectile component
        /// @param parentNetId The parent network Id
        AlliedProjectile(unsigned short parentNetId = 0) : parentNetworkId(parentNetId){};

        /// @brief Destroy the Allied Projectile object
        ~AlliedProjectile() = default;
    };
} // namespace rtypelogic::global
#endif /* !PROJECTILEALLYCOMPONENT_HPP_ */
