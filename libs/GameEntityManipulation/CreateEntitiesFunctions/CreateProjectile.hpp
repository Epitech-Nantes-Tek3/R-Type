/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** CreateProjectile
*/

#ifndef CREATEPROJECTILE_HPP_
#define CREATEPROJECTILE_HPP_

#include "World/World.hpp"
#include "GameComponents/CollidableComponent.hpp"
#include "GameComponents/DamageComponent.hpp"
#include "GameComponents/DamageRadiusComponent.hpp"
#include "GameComponents/LifeComponent.hpp"
#include "GameComponents/LifeTimeComponent.hpp"
#include "GameComponents/PositionComponent.hpp"
#include "GameComponents/ProjectileComponent.hpp"
#include "GameComponents/SizeComponent.hpp"
#include "GameComponents/VelocityComponent.hpp"
#include "GameComponents/WeightComponent.hpp"

namespace ecs
{
    /// @brief This function can create a new Projectile Entity in the world pass in params
    /// @param world The world in that the Projectile must be created
    /// @param pos_x The start position x of the new Projectile
    /// @param pos_y The start position y of the new Projectile
    /// @param multiplierAbscissa The Velocity multiplierAbscissa of the new Projectile
    /// @param multiplierOrdinate The Velocity multiplierOrdinate of the new Projectile
    /// @param damage The Damage of the new Projectile
    /// @return  Id of the new Projectile in std::size_t
    inline std::size_t createNewProjectile(World &world, const int pos_x, const int pos_y,
        const double multiplierAbscissa, const double multiplierOrdinate, const unsigned short damage)
    {
        return world.addEntity()
            .addComponent<Position>(pos_x, pos_y)
            .addComponent<Weight>(1)
            .addComponent<Size>(2, 1)
            .addComponent<Lifetime>()
            .addComponent<Life>(10)
            .addComponent<Damage>(damage)
            .addComponent<DamageRadius>(5)
            .addComponent<Collidable>()
            .addComponent<Projectile>()
            .addComponent<Velocity>(multiplierAbscissa, multiplierOrdinate)
            .getId();
    }
} // namespace ecs
#endif /* !CREATEPROJECTILE_HPP_ */
