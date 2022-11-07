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
        const unsigned short life, const unsigned short damage, const unsigned short damageRadius, unsigned short type,
        const std::string uuid, const unsigned short networkId)
    {
        Entity &entity = world.addEntity();
        auto guard = std::lock_guard(entity);
        RandomDevice &random = world.getResource<RandomDevice>();
        auto randomguard = std::lock_guard(random);
        entity.addComponent<Position>(posX, posY)
            .addComponent<Weight>(weight)
            .addComponent<Size>(sizeX, sizeY)
            .addComponent<Life>(life)
            .addComponent<Damage>(damage)
            .addComponent<DamageRadius>(damageRadius)
            .addComponent<Collidable>()
            .addComponent<Velocity>(multiplierAbscissa, multiplierOrdinate)
            .addComponent<Enemy>(type)
            .addComponent<Destination>(
                random.randInt(MINIMUM_WIDTH, MAXIMUM_WIDTH), random.randInt(MINIMUM_HEIGTH, MAXIMUM_HEIGTH));
        switch (type) {
            case Enemy::FIRE: entity.addComponent<ShootingFrequency>(2); break;
            case Enemy::ELECTRIC: entity.addComponent<ShootingFrequency>(0.5); break;
            case Enemy::ICE: entity.addComponent<ShootingFrequency>(1); break;
            default:
                entity.addComponent<ShootingFrequency>(1.5);
                break;
                ;
        };
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
            entity.addComponent<LayerLvL>(LayerLvL::layer_e::ENEMY);
        }
        return entity.getId();
    }

    std::size_t createNewEnemyRandom(World &world, const double multiplierAbscissa, const double multiplierOrdinate,
        const short weight, const int sizeX, const int sizeY, const unsigned short life, const unsigned short damage,
        const unsigned short damageRadius, unsigned short type, const std::string uuid, const unsigned short networkId)
    {
        RandomDevice &random = world.getResource<RandomDevice>();
        random.lock();
        int posX = random.randInt(MINIMUM_WIDTH, MAXIMUM_WIDTH);
        int posY = random.randInt(MINIMUM_HEIGTH, MAXIMUM_HEIGTH);
        random.unlock();
        return createNewEnemy(world, posX, posY, multiplierAbscissa, multiplierOrdinate, weight, sizeX, sizeY, life,
            damage, damageRadius, type, uuid, networkId);
    }

    std::size_t createBasicEnemy(World &world, const unsigned short networkId)
    {
        return createNewEnemyRandom(world, 0, 0, 5, 68, 68, 30, 10, 3, Enemy::BASIC, "", networkId);
    }

    std::size_t createFireEnemy(World &world, const unsigned short networkId)
    {
        return createNewEnemyRandom(world, 0, 0, 10, 102, 102, 30, 50, 10, Enemy::FIRE, "", networkId);
    }

    std::size_t createElectricEnemy(World &world, const unsigned short networkId)
    {
        return createNewEnemyRandom(world, 0, 0, 1, 34, 34, 25, 20, 1, Enemy::ELECTRIC, "", networkId);
    }

    std::size_t createIceEnemy(World &world, const unsigned short networkId)
    {
        return createNewEnemy(world, 0, 0, 0, 0, 1, 85, 85, 20, 5, 20, Enemy::ICE, "", networkId);
    }
} // namespace ecs
