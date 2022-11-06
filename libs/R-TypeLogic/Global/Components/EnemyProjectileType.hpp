/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** R-TypeileType
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
        unsigned short parentType;

        /// @brief Construct the projectile component with the parent's type
        EnemyProjectileType(unsigned short newType = Enemy::BASIC) : parentType(newType) {};

        /// @brief Default Destructor
        ~EnemyProjectileType() = default;
    };

} // namespace ecs

#endif /* !PROJECTILETYPE_HPP_ */
