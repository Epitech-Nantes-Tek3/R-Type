/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** CreateObstacle
*/

#include "CreateObstacle.hpp"

namespace ecs
{

    std::size_t createNewObstacle(World &world, const int posX, const int posY, const unsigned short damage,
        const std::string uuid, unsigned short networkId)
    {
        Entity &entity = world.addEntity()
                             .addComponent<Position>(posX, posY)
                             .addComponent<Weight>(1)
                             .addComponent<Size>(1, 1)
                             .addComponent<Life>(10)
                             .addComponent<Damage>(damage)
                             .addComponent<DamageRadius>(5)
                             .addComponent<Collidable>()
                             .addComponent<Obstacle>();

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
            entity.addComponent<LayerLvL>(LayerLvL::layer_e::OBSTACLE);
        }
        return entity.getId();
    }
} // namespace ecs