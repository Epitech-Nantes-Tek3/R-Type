/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** CreatePlayer
*/

#include "CreatePlayer.hpp"

namespace ecs
{
    std::size_t createNewPlayer(World &world, const int posX, const int posY, const double multiplierAbscissa,
        const double multiplierOrdinate, const short weight, const int sizeX, const int sizeY,
        const unsigned short life, const unsigned short damage, const unsigned short damageRadius, bool controlable,
        const std::string uuid, unsigned short networkId)
    {
        Entity &entity = world.addEntity()
                             .addComponent<Position>(posX, posY)
                             .addComponent<Weight>(weight)
                             .addComponent<Size>(sizeX, sizeY)
                             .addComponent<LifeTime>()
                             .addComponent<Life>(life)
                             .addComponent<Damage>(damage)
                             .addComponent<DamageRadius>(damageRadius)
                             .addComponent<Collidable>()
                             .addComponent<ShootingFrequency>(0.05)
                             .addComponent<Velocity>(multiplierAbscissa, multiplierOrdinate)
                             .addComponent<Player>();
        if (controlable == true) {
            entity.addComponent<Controlable>();
        }
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
            entity.addComponent<LayerLvL>(LayerLvL::layer_e::PLAYER);
        }
        return entity.getId();
    }
} // namespace ecs