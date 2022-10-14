/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** CreateAlliedProjectile
*/

#ifndef CREATEALLYPROJECTILE_HPP_
#define CREATEALLYPROJECTILE_HPP_

#include "GameComponents/AlliedProjectileComponent.hpp"
#include "GameComponents/CollidableComponent.hpp"
#include "GameComponents/DamageComponent.hpp"
#include "GameComponents/DamageRadiusComponent.hpp"
#include "GameComponents/LifeComponent.hpp"
#include "GameComponents/LifeTimeComponent.hpp"
#include "GameComponents/PositionComponent.hpp"
#include "GameComponents/SizeComponent.hpp"
#include "GameComponents/VelocityComponent.hpp"
#include "GameComponents/WeightComponent.hpp"
#include "World/World.hpp"

namespace ecs
{
    /// @brief This function creates a new Entity projectile_ally when an ally shoot
    /// @param world The world in which the Enemy must be created
    /// @param ally Entity who fired an ally projectile
    /// @return Id in size_t of the new Entity
    inline std::size_t createNewAlliedProjectile(World &world, Entity &ally)
    {
        Position pos = ally.getComponent<Position>();
        Damage damage = ally.getComponent<Damage>();
        Velocity velocity = ally.getComponent<Velocity>();

        return world.addEntity()
            .addComponent<Position>(pos.x, pos.y)
            .addComponent<Velocity>(velocity.multiplierAbscissa, velocity.multiplierOrdinate)
            .addComponent<Weight>(1)
            .addComponent<Size>(2, 1)
            .addComponent<LifeTime>()
            .addComponent<Life>(10)
            .addComponent<Damage>(damage)
            .addComponent<DamageRadius>(5)
            .addComponent<Collidable>()
            .addComponent<AlliedProjectile>()
            .getId();
    }
} // namespace ecs
#endif /* !CREATEALLYPROJECTILE_HPP_ */
