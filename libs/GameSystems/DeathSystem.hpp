/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** DeathSystem
*/

#ifndef DEATHSYSTEM_HPP_
#define DEATHSYSTEM_HPP_

#include "GameComponents/DeathComponent.hpp"
#include "GameEntityManipulation/CreateEntitiesFunctions/CreateEnemy.hpp"
#include "Transisthor/TransisthorECSLogic/Server/Resources/NetworkableIdGenerator.hpp"
#include "World/World.hpp"

namespace ecs
{
    /// @brief This is the Death System. This system takes all entities which have Dead Component and
    /// removes them from the world.
    /// It's a system that will be called by the engine world with the function runSystem()
    struct DeathSystem : public System {
        inline void run(World &world) override final
        {
            std::vector<std::shared_ptr<ecs::Entity>> joined = world.joinEntities<Death>();

            auto death = [&world](std::shared_ptr<ecs::Entity> entityPtr) {
                if (entityPtr->contains<Enemy>() == true)
                    createNewEnemyRandom(world, 1, 1, 1, 4, 4, 100, 10, 5, "",
                        world.getResource<NetworkableIdGenerator>().generateNewNetworkableId());
                world.removeEntity(entityPtr->getId());
            };
            std::for_each(joined.begin(), joined.end(), death);
        }
    };
} // namespace ecs

#endif /* !DEATHSYSTEM_HPP_ */
