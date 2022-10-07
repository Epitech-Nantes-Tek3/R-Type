/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** CreateAllyProjectile
*/

#ifndef CREATEALLYPROJECTILE_HPP_
#define CREATEALLYPROJECTILE_HPP_

#include <World/World.hpp>
#include <GameComponents/PositionComponent.hpp>
#include <GameComponents/VelocityComponent.hpp>
#include <GameComponents/WeightComponent.hpp>
#include <GameComponents/SizeComponent.hpp>
#include <GameComponents/LifetimeComponent.hpp>
#include <GameComponents/DamageComponent.hpp>
#include <GameComponents/LifeComponent.hpp>
#include <GameComponents/DamageComponent.hpp>
#include <GameComponents/DamageRadiusComponent.hpp>
#include <GameComponents/CollidableComponent.hpp>
#include <GameComponents/ProjectileAllyComponent.hpp>

using namespace ecs;

/// @brief This function create a new Entity projectile_ally when an ally shoot
/// @param world 
/// @param ally Ally who fired
/// @return Id in size_t of the new Entity
inline std::size_t createNewAllyProjectile(World *world, Entity &ally)
{
    Position pos = ally.getComponent<Position>();
    Damage damage = ally.getComponent<Damage>();
    Velocity velocity = ally.getComponent<Velocity>();

    std::size_t new_projectile = world->addEntity()
                                        .addComponent<Position>(pos.x, pos.y)
                                        .addComponent<Velocity>(velocity.multiplierAbscissa, velocity.multiplierOrdinate)
                                        .addComponent<Weight>(1)
                                        .addComponent<Size>(2, 1)
                                        .addComponent<Lifetime>()
                                        .addComponent<Life>(10)
                                        .addComponent<Damage>(damage)
                                        .addComponent<DamageRadius>(5)
                                        .addComponent<Collidable>()
                                        .addComponent<ProjectileAlly>()
                                        .getId();
    return new_projectile;
}

#endif /* !CREATEALLYPROJECTILE_HPP_ */
