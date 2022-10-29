/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** CreateEnemy
*/

#include "CreateEnemy.hpp"
#include <mutex>

namespace ecs
{
    std::size_t createNewEnemy(World &world, const int posX, const int posY, const double multiplierAbscissa,
        const double multiplierOrdinate, const short weight, const int sizeX, const int sizeY,
        const unsigned short life, const unsigned short damage, const unsigned short damageRadius,
        const std::string uuid, const unsigned short networkId)
    {
        Entity &entity = world.addEntity();
        auto guard = std::lock_guard(entity);
        entity.addComponent<Position>(posX, posY)
            .addComponent<Weight>(weight)
            .addComponent<Size>(sizeX, sizeY)
            .addComponent<Life>(life)
            .addComponent<Damage>(damage)
            .addComponent<DamageRadius>(damageRadius)
            .addComponent<Collidable>()
            .addComponent<Velocity>(multiplierAbscissa, multiplierOrdinate)
            .addComponent<Enemy>();

        if (networkId) {
            // Case : Creation in a server instance
            RandomDevice &random = world.getResource<RandomDevice>();
            auto guard = std::lock_guard(random);
            entity.addComponent<NewlyCreated>(uuid, false);
            entity.addComponent<Networkable>(networkId);
            entity.addComponent<ShootingFrequency>(1.3);
            entity.addComponent<Destination>(
                random.randInt(MINIMUM_WIDTH, MAXIMUM_WIDTH), random.randInt(MINIMUM_HEIGTH, MAXIMUM_HEIGTH));
        } else {
            // Case : Creation in a Client instance
            if (uuid != "") {
                // Special case : the client created the entity and not the server
                entity.addComponent<NewlyCreated>(uuid, true);
            }
            entity.addComponent<LayerLvL>(LayerLvL::layer_e::ENEMY);
        }
        return entity.getId();
    }

    std::size_t createNewEnemyRandom(World &world, const double multiplierAbscissa, const double multiplierOrdinate,
        const short weight, const int sizeX, const int sizeY, const unsigned short life, const unsigned short damage,
        const unsigned short damageRadius, const std::string uuid, const unsigned short networkId)
    {
        RandomDevice &random = world.getResource<RandomDevice>();
        random.lock();
        int posX = random.randInt(MINIMUM_WIDTH, MAXIMUM_WIDTH);
        int posY = random.randInt(MINIMUM_HEIGTH, MAXIMUM_HEIGTH);
        random.unlock();
        return createNewEnemy(world, posX, posY, multiplierAbscissa, multiplierOrdinate, weight, sizeX, sizeY, life,
            damage, damageRadius, uuid, networkId);
    }
} // namespace ecs
