/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** EnemyProjectileComponent
*/

#ifndef EnemyProjectileCOMPONENT_HPP_
#define EnemyProjectileCOMPONENT_HPP_

#include "Component/Component.hpp"

namespace rtypelogic::global
{
    /// @brief Enemy Projectile Component allows an entity to be used as an Enemy Projectile
    class EnemyProjectile : public ecs::Component {
      public:
        /// @brief Network id of the parent
        unsigned short parentNetworkId;

        /// @brief Construct a new EnemyProjectile component
        /// @param parentNetId The parent network Id
        EnemyProjectile(unsigned short parentNetId = 0) : parentNetworkId(parentNetId){};

        /// @brief Destroy the Enemy Projectile object
        ~EnemyProjectile() = default;
    };
} // namespace rtypelogic::global
#endif /* !EnemyProjectileCOMPONENT_HPP_ */
