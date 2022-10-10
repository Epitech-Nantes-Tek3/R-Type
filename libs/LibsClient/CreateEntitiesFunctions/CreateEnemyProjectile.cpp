/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** CreateEnemyProjectile
*/

#include "CreateEnemyProjectile.hpp"

namespace ecs
{
    std::size_t createNewEnemyProjectile(World &world, Entity &enemy)
    {
        Position pos = enemy.getComponent<Position>();
        Damage damage = enemy.getComponent<Damage>();
        Velocity velocity = enemy.getComponent<Velocity>();

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
                .addComponent<EnemyProjectile>()
                .getId();
        return new_projectile;
    }
} // namespace ecs