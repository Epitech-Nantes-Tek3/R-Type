/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** CreateAlliedProjectile
*/

#include "CreateAlliedProjectile.hpp"

namespace ecs
{
    std::size_t createNewAlliedProjectile(World &world, Entity &allied) {
        Position pos = allied.getComponent<Position>();
        Damage damage = allied.getComponent<Damage>();
        Velocity velocity = allied.getComponent<Velocity>();

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
                .addComponent<AlliedProjectile>()
                .getId();
        return new_projectile;
    }
} // namespace ecs