/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** CreateEnemyProjectile
*/

#ifndef CREATEENEMYPROJECTILE_HPP_
#define CREATEENEMYPROJECTILE_HPP_

#include "World/World.hpp"
#include <GameComponents/PositionComponent.hpp>
#include <GameComponents/VelocityComponent.hpp>
#include <GameComponents/WeightComponent.hpp>
#include <GameComponents/SizeComponent.hpp>
#include <GameComponents/LifeTimeComponent.hpp>
#include <GameComponents/DamageComponent.hpp>
#include <GameComponents/LifeComponent.hpp>
#include <GameComponents/DamageComponent.hpp>
#include <GameComponents/DamageRadiusComponent.hpp>
#include <GameComponents/CollidableComponent.hpp>
#include <GameComponents/ProjectileEnemyComponent.hpp>

using namespace ecs;

/// @brief This function create a new Entity projectile_enemy when an enemy shoot
/// @param world The world in that the EnemyProjectile must be created
/// @param enemy Enemy who fired
/// @return Id in size_t of the new Entity
inline std::size_t createNewEnemyProjectile(World &world, Entity &enemy)
{
    Position pos = enemy.getComponent<Position>();
    Damage damage = enemy.getComponent<Damage>();
    Velocity velocity = enemy.getComponent<Velocity>();

    std::size_t new_projectile = world.addEntity()
                                        .addComponent<Position>(pos.x, pos.y)
                                        .addComponent<Velocity>(velocity.multiplierAbscissa, velocity.multiplierOrdinate)
                                        .addComponent<Weight>(1)
                                        .addComponent<Size>(2, 1)
                                        .addComponent<Lifetime>()
                                        .addComponent<Life>(10)
                                        .addComponent<Damage>(damage)
                                        .addComponent<DamageRadius>(5)
                                        .addComponent<Collidable>()
                                        .addComponent<ProjectileEnemy>()
                                        .getId();
    return new_projectile;
}

#endif /* !CREATEENEMYPROJECTILE_HPP_ */
