/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** DeathSystem
*/

#ifndef DEATHSYSTEM_HPP_
#define DEATHSYSTEM_HPP_

#include "World/World.hpp"
#include "Component/DeathComponent.hpp"

namespace ecs
{
    /// @brief This is the Death System. This system take all entities which have Dead Component and
    /// remove it of the world. It's a system that will be called by the engine world with the function runSystem()
    struct Death : public System {
        inline void run(World &world) override final
        {
            std::vector<std::shared_ptr<ecs::Entity>> joined = world.joinEntities<Death>();

            auto move = [](World &world, std::shared_ptr<ecs::Entity> entityPtr) {
                world.removeEntity(entityPtr->getId())
            };
            std::for_each(joined.begin(), joined.end(), move);
        }
    };
} // namespace ecs

#endif /* !DEATHSYSTEM_HPP_ */
