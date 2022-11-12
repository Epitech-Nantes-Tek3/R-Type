/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** DeathSystem
*/

#ifndef DEATHSYSTEM_HPP_
#define DEATHSYSTEM_HPP_

#include <mutex>
#include "Transisthor/TransisthorECSLogic/Server/Resources/NetworkableIdGenerator.hpp"
#include "World/World.hpp"
#include "R-TypeLogic/EntityManipulation/CreateEntitiesFunctions/CreateEnemy.hpp"
#include "R-TypeLogic/Global/Components/DeathComponent.hpp"
#include "R-TypeLogic/Global/Components/EnemyComponent.hpp"
#include "R-TypeLogic/Global/SharedResources/GameLevel.hpp"
#include "R-TypeLogic/Global/SharedResources/GlobalScore.hpp"

namespace ecs
{    /// @brief This is the Death System. This system takes all entities which have Dead Component and
    /// removes them from the world.
    /// It's a system that will be called by the engine world with the function runSystem()
    struct DeathSystem : public System {
        inline void run(World &world) override final
        {
            std::vector<std::shared_ptr<ecs::Entity>> joined = world.joinEntities<Death>();

            auto death = [&world](std::shared_ptr<ecs::Entity> entityPtr) {
                auto guard = std::lock_guard(*entityPtr.get());
                if (entityPtr.get()->getComponent<Death>().modified != true) {
                    if (entityPtr->contains<Enemy>()) {
                        if (world.containsResource<GameLevel>()) {
                            GameLevel &gameLevel = world.getResource<GameLevel>();
                            gameLevel.lock();
                            gameLevel.addNewKills();
                            gameLevel.unlock();
                        }
                        if (world.containsResource<GlobalScore>()) {
                            GlobalScore &gbScore = world.getResource<GlobalScore>();
                            gbScore.lock();
                            gbScore.updateScore(entityPtr->getComponent<Enemy>().enemyType);
                            gbScore.unlock();
                        }
                    }
                    world.removeEntity(entityPtr->getId());
                }
            };
            std::for_each(joined.begin(), joined.end(), death);
        }
    };
}// namespace ecs

#endif /* !DEATHSYSTEM_HPP_ */
