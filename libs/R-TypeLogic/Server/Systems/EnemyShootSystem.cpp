/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** EnemyShootSystem
*/

#include "EnemyShootSystem.hpp"
#include <chrono>
#include <iostream>
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
        auto guard = std::lock_guard(*entityPtr.get());
        ShootingFrequency &freq = entityPtr.get()->getComponent<ShootingFrequency>();

       if (freq.frequency == duration<double>(0)) {
            if (world.containsResource<NetworkableIdGenerator>()) {
                NetworkableIdGenerator &generator = world.getResource<NetworkableIdGenerator>();
                auto guard = std::lock_guard(generator);
                createNewEnemyProjectile(world, entityPtr, "", generator.generateNewNetworkableId());
                freq.frequency = freq.baseFrequency;
            } else {
                createNewEnemyProjectile(world, entityPtr, "");
                freq.frequency = freq.baseFrequency;
            }
        }
    };
    std::for_each(joined.begin(), joined.end(), enemiesMayShoot);
 }
