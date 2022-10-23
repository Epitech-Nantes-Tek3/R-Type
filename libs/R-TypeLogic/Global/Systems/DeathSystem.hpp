/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** DeathSystem
*/

#ifndef DEATHSYSTEM_HPP_
#define DEATHSYSTEM_HPP_

#include "Transisthor/ECSLogic/Server/Resources/NetworkableIdGenerator.hpp"
#include "World/World.hpp"
#include "R-TypeLogic/EntityManipulation/CreateEntitiesFunctions/CreateEnemy.hpp"
#include "R-TypeLogic/Global/Components/DeathComponent.hpp"

namespace rtypelogic
{
    using namespace entitymanipulation;
    namespace global
    {
        /// @brief This is the Death System. This system takes all entities which have Dead Component and
        /// removes them from the world.
        /// It's a system that will be called by the engine world with the function runSystem()
        struct DeathSystem : public ecs::System {
            inline void run(World &world) override final
            {
                std::vector<std::shared_ptr<ecs::Entity>> joined = world.joinEntities<Death>();

                auto death = [&world](std::shared_ptr<ecs::Entity> entityPtr) {
                    if (entityPtr->contains<Enemy>() == true)
                        createNewEnemyRandom(world, 0, 0, 1, 4, 4, 100, 10, 5, "",
                            world.getResource<NetworkableIdGenerator>().generateNewNetworkableId());
                    world.removeEntity(entityPtr->getId());
                };
                std::for_each(joined.begin(), joined.end(), death);
            }
        };
    } // namespace global
} // namespace rtypelogic

#endif /* !DEATHSYSTEM_HPP_ */