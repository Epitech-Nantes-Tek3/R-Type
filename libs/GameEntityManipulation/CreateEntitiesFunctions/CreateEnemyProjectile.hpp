/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** CreateEnemyProjectile
*/

#ifndef CREATEENEMYPROJECTILE_HPP_
#define CREATEENEMYPROJECTILE_HPP_

#include "GameComponents/CollidableComponent.hpp"
#include "GameComponents/DamageComponent.hpp"
#include "GameComponents/DamageRadiusComponent.hpp"
#include "GameComponents/EnemyProjectileComponent.hpp"
#include "GameComponents/LifeComponent.hpp"
#include "GameComponents/LifeTimeComponent.hpp"
#include "GameComponents/PositionComponent.hpp"
#include "GameComponents/SizeComponent.hpp"
#include "GameComponents/Uuid.hpp"
#include "GameComponents/VelocityComponent.hpp"
#include "GameComponents/WeightComponent.hpp"
#include "GameSharedResources/Random.hpp"
#include "World/World.hpp"

namespace ecs
{

    /// @brief This function create a new Entity projectile_enemy when an enemy shoot
    /// @param world The world in which the EnemyProjectile must be created
    /// @param enemy Enemy who fired
    /// @return Id in size_t of the new Entity
    std::size_t createNewEnemyProjectile(World &world, Entity &enemy)
    {
        Position pos = enemy.getComponent<Position>();
        Damage damage = enemy.getComponent<Damage>();
        Velocity velocity = enemy.getComponent<Velocity>();

        return world.addEntity()
            .addComponent<Uuid>(world.getResource<RandomDevice>().getRandomDevice(), 16)
            .addComponent<Position>(pos.x, pos.y)
            .addComponent<Velocity>(velocity.multiplierAbscissa, velocity.multiplierOrdinate)
            .addComponent<Weight>(1)
            .addComponent<Size>(2, 1)
            .addComponent<LifeTime>()
            .addComponent<Life>(10)
            .addComponent<Damage>(damage)
            .addComponent<DamageRadius>(5)
            .addComponent<Collidable>()
            .addComponent<EnemyProjectile>()
            .getId();
    }
} // namespace ecs
#endif /* !CREATEENEMYPROJECTILE_HPP_ */
