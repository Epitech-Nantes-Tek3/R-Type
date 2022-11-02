/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** ProjectileType
*/

#ifndef ENEMYPROJECTILETYPE_HPP_
#define ENEMYPROJECTILETYPE_HPP_

#include "Component/Component.hpp"
#include "EnemyComponent.hpp"

namespace ecs
{
    /// @brief The projectile enemy type, useful for the graphical display
    class EnemyProjectileType : public Component {
      public:
        /// @brief The enemy projectile type, given by its parent
        Enemy::type_e parentType;

        /// @brief Construct the projectile component with the parent's type
        EnemyProjectileType(Enemy::type_e newType = Enemy::BASIC) : parentType(newType) {};

        /// @brief Default Destructor
        ~EnemyProjectileType();
    };

} // namespace ecs

#endif /* !PROJECTILETYPE_HPP_ */
