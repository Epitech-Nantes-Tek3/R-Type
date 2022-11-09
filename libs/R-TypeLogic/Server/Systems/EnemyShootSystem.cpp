/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** EnemyShootSystem
*/

#include "EnemyShootSystem.hpp"
#include <chrono>
#include <mutex>
#include "Transisthor/TransisthorECSLogic/Server/Resources/NetworkableIdGenerator.hpp"
#include "R-TypeLogic/EntityManipulation/CreateEntitiesFunctions/CreateEnemy.hpp"
#include "R-TypeLogic/EntityManipulation/CreateEntitiesFunctions/CreateEnemyProjectile.hpp"
#include "R-TypeLogic/Global/Components/EnemyComponent.hpp"
#include "R-TypeLogic/Global/Components/ShootingFrequencyComponent.hpp"
#include "R-TypeLogic/Global/SharedResources/GameClock.hpp"
#include "R-TypeLogic/Global/SharedResources/Random.hpp"

using namespace ecs;
using namespace std::chrono;

/// @brief This function generates a mob from the boss when a boss should shoot
/// @param world the world where the new enemy will be generated
/// @param pos the world where the new enemy will be generated
/// @param networkdId the networkId of the new enemy, 0 if it's in solo mod
static void bossGeneration(World &world, Position &pos, unsigned int networkId)
{
    unsigned int enemyType = 0;

    if (world.containsResource<RandomDevice>()) {
        RandomDevice &random = world.getResource<RandomDevice>();

        random.lock();
        enemyType = random.randInt(0, 2);
        random.unlock();
    }
    createBossPawn(world, pos, enemyType, networkId);
}

void EnemyShootSystem::run(World &world)
{
    std::vector<std::shared_ptr<ecs::Entity>> joined = world.joinEntities<Enemy, ShootingFrequency>();

    auto enemiesMayShoot = [&world](std::shared_ptr<ecs::Entity> entityPtr) {
        auto guard = std::lock_guard(*entityPtr.get());
        ShootingFrequency &freq = entityPtr.get()->getComponent<ShootingFrequency>();

        if (freq.frequency == duration<double>(0)) {
            if (world.containsResource<NetworkableIdGenerator>()) {
                NetworkableIdGenerator &generator = world.getResource<NetworkableIdGenerator>();
                auto guard = std::lock_guard(generator);
                unsigned int networkId = generator.generateNewNetworkableId();

                if (entityPtr->getComponent<Enemy>().enemyType == Enemy::BOSS) {
                    bossGeneration(world, entityPtr->getComponent<Position>(), networkId);
                } else {
                    createNewEnemyProjectile(world, entityPtr, "", networkId);
                }
                freq.frequency = freq.baseFrequency;
            } else {
                if (entityPtr->getComponent<Enemy>().enemyType == Enemy::BOSS) {
                    bossGeneration(world, entityPtr->getComponent<Position>(), 0);
                } else {
                    createNewEnemyProjectile(world, entityPtr, "");
                }
                freq.frequency = freq.baseFrequency;
            }
        }
    };
    std::for_each(joined.begin(), joined.end(), enemiesMayShoot);
}