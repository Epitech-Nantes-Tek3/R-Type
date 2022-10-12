/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** CreateEnemyRandomPosition
*/

#ifndef CREATEENEMYRANDOMPOSITION_HPP_
#define CREATEENEMYRANDOMPOSITION_HPP_

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
#include "GameSharedResources/Random.hpp"
#include "World/World.hpp"

namespace ecs
{
    
    /// @brief This function create a new Enemy Entity with random position and with these parameters
    /// @param world The world in which the Enemy must be created
     /// @param multiplierAbscissa The Velocity multiplierAbscissa for the new Enemy
    /// @param multiplierOrdinate The Velocity multiplierOrdinate for the new Enemy
    /// @param weight Weight of the Enemy
    /// @param size_x Size x of the Enemy
    /// @param size_y Size y of the Enemy
    /// @param life Life of the Enemy
    /// @param damage Damage of projectiles fired by this Enemy
    /// @param damageRadius DamageRadius of projectiles fired by this Enemy
    /// @return Id of the new Enemy in std::size_t
    std::size_t createNewEnemyRandom(World &world, const double multiplierAbscissa, const double multiplierOrdinate, const short weight, const int size_x, const int size_y, const unsigned short life, const unsigned short damage, const unsigned short damageRadius)
    {
        return world.addEntity()
            .addComponent<Position>(world.getResource<RandomDevice>().randInt(1400, 1920),
                world.getResource<RandomDevice>().randInt(0, 1080))
            .addComponent<Weight>(weight)
            .addComponent<Size>(size_x, size_y)
            .addComponent<Lifetime>()
            .addComponent<Life>(life)
            .addComponent<Damage>(damage)
            .addComponent<DamageRadius>(damageRadius)
            .addComponent<Collidable>()
            .addComponent<Velocity>(multiplierAbscissa, multiplierOrdinate)
            .addComponent<Enemy>()
            .getId();
    }

} // namespace ecs
#endif /* !CREATEENEMYRANDOMPOSITION_HPP_ */
