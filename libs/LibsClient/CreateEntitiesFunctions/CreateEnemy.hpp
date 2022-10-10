/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** CreateEnemy
*/

#ifndef CREATEENEMY_HPP_
#define CREATEENEMY_HPP_

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
#include <GameComponents/EnemyComponent.hpp>

using namespace ecs;

/// @brief This function create a new Enemy Entity with these parameters
/// @param world The world in that the Enemy must be created
/// @param pos Position of the Enemy
/// @param weight Weight of the Enemy
/// @param size Size of the player
/// @param life Life of the Enemy
/// @param damage Damage of projectiles fired by this Enemy
/// @param damageRadius DamageRadius of projectiles fired by this Enemy
/// @return Id of the new Enemy in std::size_t
inline std::size_t createNewEnemy(World &world, Position &pos, Weight &weight, Size &size, Life &life, Damage &damage, DamageRadius &damageRadius)
{
    std::size_t new_enemy = world.addEntity()
                                .addComponent<Position>(pos.x, pos.y)
                                .addComponent<Weight>(weight)
                                .addComponent<Size>(size.x, size.y)
                                .addComponent<Lifetime>()
                                .addComponent<Life>(life)
                                .addComponent<Damage>(damage)
                                .addComponent<DamageRadius>(damageRadius)
                                .addComponent<Collidable>()
                                .addComponent<Enemy>()
                                .getId();
    return new_enemy;
}

#endif /* !CREATEENEMY_HPP_ */