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
#include "R-TypeLogic/EntityManipulation/CreateEntitiesFunctions/CreateEnemyProjectile.hpp"
#include "R-TypeLogic/Global/Components/EnemyComponent.hpp"
#include "R-TypeLogic/Global/Components/ShootingFrequencyComponent.hpp"
#include "R-TypeLogic/Global/SharedResources/GameClock.hpp"

using namespace ecs;
using namespace std::chrono;

void EnemyShootSystem::run(World &world)
{
    std::vector<std::shared_ptr<ecs::Entity>> joined = world.joinEntities<Enemy, ShootingFrequency>();

    auto enemiesMayShoot = [&world](std::shared_ptr<ecs::Entity> entityPtr) {
        std::lock_guard(*entityPtr.get());
        ShootingFrequency &freq = entityPtr.get()->getComponent<ShootingFrequency>();

        if (freq.frequency == duration<double>(0)) {
            createNewEnemyProjectile(
                world, entityPtr, "", world.getResource<NetworkableIdGenerator>().generateNewNetworkableId());
            freq.frequency = freq.baseFrequency;
        }
    };
    std::for_each(joined.begin(), joined.end(), enemiesMayShoot);
}
