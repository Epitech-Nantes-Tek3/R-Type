/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** CreatePlayer
*/

#ifndef CREATEPLAYER_HPP_
#define CREATEPLAYER_HPP_

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
#include <GameComponents/PlayerComponent.hpp>

using namespace ecs;

/// @brief This function creates a new Player Entity with these parameters
/// @param world The world in that the Player must be created
/// @param pos Position of the Player
/// @param weight Weight of the Player
/// @param size Size of the player
/// @param life Life of the Player
/// @param damage Damage of projectiles fired by this Player
/// @param damageRadius DamageRadius of projectiles fired by this Player
/// @return Id of the new Player in std::size_t
inline std::size_t createNewPlayer(World &world, Position &pos, Weight &weight, Size &size, Life &life, Damage &damage, DamageRadius &damageRadius)
{
    std::size_t new_player = world.addEntity()
                                .addComponent<Position>(pos.x, pos.y)
                                .addComponent<Weight>(weight)
                                .addComponent<Size>(size.x, size.y)
                                .addComponent<Lifetime>()
                                .addComponent<Life>(life)
                                .addComponent<Damage>(damage)
                                .addComponent<DamageRadius>(damageRadius)
                                .addComponent<Collidable>()
                                .addComponent<Player>()
                                .getId();
    return new_player;
}

#endif /* !CREATEPLAYER_HPP_ */
