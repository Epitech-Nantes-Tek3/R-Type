/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** CreateEnemyProjectile
*/

#include "CreateEnemyProjectile.hpp"
#include <mutex>
#include "R-TypeLogic/Global/Components/EnemyProjectileType.hpp"

namespace ecs
{

    /// @brief Create a Basic projectile with specific values
    /// @param projectile a reference to the projectile entity to be modified
    static void createBasicProjectile(Entity &projectile)
    {
        projectile.addComponent<Velocity>(-300, 0)
            .addComponent<Weight>(3)
            .addComponent<Size>(40, 40)
            .addComponent<LifeTime>(3)
            .addComponent<Life>(1)
            .addComponent<Damage>(25)
            .addComponent<DamageRadius>(5);
    }
    /// @brief Create a fire projectile with specific values
    /// @param projectile a reference to the projectile entity to be modified
    static void createFireProjectile(Entity &projectile) {
        projectile.addComponent<Velocity>(-250, 0)
            .addComponent<Weight>(5)
            .addComponent<Size>(60, 60)
            .addComponent<LifeTime>(7)
            .addComponent<Life>(20)
            .addComponent<Damage>(40)
            .addComponent<DamageRadius>(10);
    }

    /// @brief Create a Electric projectile with specific values
    /// @param projectile a reference to the projectile entity to be modified
    static void createElectricProjectile(Entity &projectile) {
        projectile.addComponent<Velocity>(-600, 0)
            .addComponent<Size>(30, 30)
            .addComponent<LifeTime>(3)
            .addComponent<Life>(1)
            .addComponent<Damage>(10)
            .addComponent<DamageRadius>(1);
    }

    /// @brief Create a Ice projectile with specific values
    /// @param projectile a reference to the projectile entity to be modified
    static void createIceProjectile(Entity &projectile) {
        projectile.addComponent<Velocity>(-400, 0)
            .addComponent<Weight>(2)
            .addComponent<Size>(40, 40)
            .addComponent<LifeTime>(10)
            .addComponent<Life>(1)
            .addComponent<Damage>(20)
            .addComponent<DamageRadius>(15);
    }

    std::size_t createNewEnemyProjectile(
        World &world, std::shared_ptr<ecs::Entity> enemy, const std::string uuid, unsigned short networkId)
    {
        Position pos = enemy.get()->getComponent<Position>();
        Damage damage = enemy.get()->getComponent<Damage>();

        Entity &entity = world.addEntity();
        auto guard = std::lock_guard(entity);
        unsigned short parentType = enemy->getComponent<Enemy>().enemyType;

        switch (parentType) {
            case Enemy::FIRE: createFireProjectile(entity); break;
            case Enemy::ELECTRIC: createElectricProjectile(entity); break;
            case Enemy::ICE: createIceProjectile(entity); break;
            default: createBasicProjectile(entity); break;
        };
        entity.addComponent<Position>(pos.x, pos.y + 20)
            .addComponent<Collidable>()
            .addComponent<EnemyProjectile>(enemy.get()->getComponent<Networkable>().id);

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
            entity.addComponent<EnemyProjectileType>(parentType);
        }
        return entity.getId();
    }
} // namespace ecs
