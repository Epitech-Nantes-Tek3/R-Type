/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** CreateAlliedProjectile
*/

#include "CreateAlliedProjectile.hpp"

namespace ecs
{
    std::size_t createNewAlliedProjectile(
        World &world, Entity &ally, const std::string uuid, unsigned short networkId)
    {
        Position pos = ally.getComponent<Position>();
        Damage damage = ally.getComponent<Damage>();
        Velocity velocity = ally.getComponent<Velocity>();

        Entity &entity = world.addEntity()
                             .addComponent<Position>(pos.x + 102, pos.y + 45)
                             .addComponent<Velocity>(300, 0)
                             .addComponent<Weight>(1)
                             .addComponent<Size>(40, 40)
                             .addComponent<LifeTime>(3)
                             .addComponent<Life>(1)
                             .addComponent<Damage>(damage)
                             .addComponent<DamageRadius>(5)
                             .addComponent<Collidable>()
                             .addComponent<AlliedProjectile>(ally.getComponent<Networkable>().id);

        if (networkId) {
            // Case : Creation in a server instance
            entity.addComponent<NewlyCreated>(uuid, false);
            entity.addComponent<Networkable>(networkId);
        } else {
            entity.addComponent<Networkable>(0);
            // Case : Creation in a Client instance
            if (uuid != "") {
                // Special case : the client created the entity and not the server
                entity.addComponent<NewlyCreated>(uuid, true);
            }
            entity.addComponent<LayerLvL>(LayerLvL::layer_e::PROJECTILE);
        }
        return entity.getId();
    }
} // namespace ecs