/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** CreateProjectile
*/

#include "CreateProjectile.hpp"

namespace ecs
{
    std::size_t createNewProjectile(World &world, const int posX, const int posY, const double multiplierAbscissa,
        const double multiplierOrdinate, const unsigned short damage, const std::string uuid,
        unsigned short networkId)
    {
        Entity &entity = world.addEntity()
                             .addComponent<Position>(posX, posY)
                             .addComponent<Weight>(1)
                             .addComponent<Size>(2, 1)
                             .addComponent<LifeTime>(4.0)
                             .addComponent<Life>(10)
                             .addComponent<Damage>(damage)
                             .addComponent<DamageRadius>(5)
                             .addComponent<Collidable>()
                             .addComponent<Projectile>()
                             .addComponent<Velocity>(multiplierAbscissa, multiplierOrdinate);

        if (networkId) {
            // Case : Creation in a server instance
            entity.addComponent<NewlyCreated>(uuid, false);
            entity.addComponent<Networkable>(networkId);
        } else {
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