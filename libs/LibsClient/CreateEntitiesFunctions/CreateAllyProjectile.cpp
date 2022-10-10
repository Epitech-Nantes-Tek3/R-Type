/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** CreateAllyProjectile
*/

#include "CreateAllyProjectile.hpp"

namespace ecs
{
    std::size_t createNewAllyProjectile(World &world, Entity &ally)
    {
        Position pos = ally.getComponent<Position>();
        Damage damage = ally.getComponent<Damage>();
        Velocity velocity = ally.getComponent<Velocity>();

        std::size_t new_projectile =
            world.addEntity()
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
} // namespace ecs