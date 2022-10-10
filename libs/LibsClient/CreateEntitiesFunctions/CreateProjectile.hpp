/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** CreateProjectile
*/

#ifndef CREATEPROJECTILE_HPP_
#define CREATEPROJECTILE_HPP_

#include <World/World.hpp>
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
#include <GameComponents/ProjectileComponent.hpp>
#include <GameComponents/VelocityComponent.hpp>

using namespace ecs;

/// @brief This function can create a new Projectile Entity in the world pass in params
/// @param world The world in that the Projectile must be created
/// @param pos The start position of the new Projectile
/// @param velocity The Velocity of the new Projectile
/// @param damage The Damage of the new Projectile
/// @return Id of the new Projectile in std::size_t
inline std::size_t createNewProjectile(World &world, Position &pos, Velocity &velocity, Damage &damage)
{
    std::size_t new_projectile = world.addEntity()
                                        .addComponent<Position>(pos.x, pos.y)
                                        .addComponent<Weight>(1)
                                        .addComponent<Size>(2, 1)
                                        .addComponent<Lifetime>()
                                        .addComponent<Life>(10)
                                        .addComponent<Damage>(damage)
                                        .addComponent<DamageRadius>(5)
                                        .addComponent<Collidable>()
                                        .addComponent<Projectile>()
                                        .addComponent<Velocity>(velocity.multiplierAbscissa, velocity.multiplierOrdinate)
                                        .getId();
    return new_projectile;
}



#endif /* !CREATEPROJECTILE_HPP_ */
