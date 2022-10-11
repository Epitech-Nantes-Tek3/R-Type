/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** CreateAlliedProjectile
*/

#include "CreateAlliedProjectile.hpp"

namespace ecs
{
    std::size_t createNewAlliedProjectile(World &world, Entity &ally)
    {
        Position pos = ally.getComponent<Position>();
        Damage damage = ally.getComponent<Damage>();
        Velocity velocity = ally.getComponent<Velocity>();

        return world.addEntity()
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
    }
} // namespace ecs