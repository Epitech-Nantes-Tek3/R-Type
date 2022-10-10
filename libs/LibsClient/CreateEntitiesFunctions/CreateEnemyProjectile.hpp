/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** CreateEnemyProjectile
*/

#ifndef CREATEENEMYPROJECTILE_HPP_
#define CREATEENEMYPROJECTILE_HPP_

#include "World/World.hpp"
#include "GameComponents/CollidableComponent.hpp"
#include "GameComponents/DamageComponent.hpp"
#include "GameComponents/DamageRadiusComponent.hpp"
#include "GameComponents/LifeComponent.hpp"
#include "GameComponents/LifeTimeComponent.hpp"
#include "GameComponents/PositionComponent.hpp"
#include "GameComponents/EnemyProjectileComponent.hpp"
#include "GameComponents/SizeComponent.hpp"
#include "GameComponents/VelocityComponent.hpp"
#include "GameComponents/WeightComponent.hpp"

namespace ecs
{

    /// @brief This function create a new Entity projectile_enemy when an enemy shoot
    /// @param world The world in that the EnemyProjectile must be created
    /// @param enemy Enemy who fired
    /// @return Id in size_t of the new Entity
    std::size_t createNewEnemyProjectile(World &world, Entity &enemy);

} // namespace ecs
#endif /* !CREATEENEMYPROJECTILE_HPP_ */
