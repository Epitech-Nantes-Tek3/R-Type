/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** CreateEnemy
*/

#ifndef CREATEENEMY_HPP_
#define CREATEENEMY_HPP_

#include "GameComponents/CollidableComponent.hpp"
#include "GameComponents/DamageComponent.hpp"
#include "GameComponents/DamageRadiusComponent.hpp"
#include "GameComponents/EnemyComponent.hpp"
#include "GameComponents/LifeComponent.hpp"
#include "GameComponents/LifeTimeComponent.hpp"
#include "GameComponents/PositionComponent.hpp"
#include "GameComponents/SizeComponent.hpp"
#include "GameComponents/VelocityComponent.hpp"
#include "GameComponents/WeightComponent.hpp"
#include "World/World.hpp"

namespace ecs
{

    /// @brief This function create a new Enemy Entity with these parameters
    /// @param world The world in that the Enemy must be created
    /// @param pos_x Position x of the Enemy
    /// @param pos_y Position y of the Enemy
    /// @param weight Weight of the Enemy
    /// @param size_x Size x of the player
    /// @param size_y Size y of the player
    /// @param life Life of the Enemy
    /// @param damage Damage of projectiles fired by this Enemy
    /// @param damageRadius DamageRadius of projectiles fired by this Enemy
    /// @return Id of the new Enemy in std::size_t
    inline std::size_t createNewEnemy(
        World &world, int pos_x, int pos_y, short weight, int size_x, int size_y, unsigned short life, unsigned short damage, unsigned short damageRadius)
    {
        std::size_t new_enemy = world.addEntity()
                                    .addComponent<Position>(pos_x, pos_y)
                                    .addComponent<Weight>(weight)
                                    .addComponent<Size>(size_x, size_y)
                                    .addComponent<Lifetime>()
                                    .addComponent<Life>(life)
                                    .addComponent<Damage>(damage)
                                    .addComponent<DamageRadius>(damageRadius)
                                    .addComponent<Collidable>()
                                    .addComponent<Enemy>()
                                    .getId();
        return new_enemy;
    }

} // namespace ecs
#endif /* !CREATEENEMY_HPP_ */