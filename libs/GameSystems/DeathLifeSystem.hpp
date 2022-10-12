/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** DeathLifeSystem
*/

#ifndef DEATHLIFESYSTEM_HPP_
#define DEATHLIFESYSTEM_HPP_

#include "World/World.hpp"
#include "GameComponents/LifeComponent.hpp"
#include "GameComponents/DeathComponent.hpp"

namespace ecs
{
    /// @brief This is the DeathLife Component. This Component take all entities which have Life 
    /// Component with 0 or under life and add Death Component to it.
    /// It's a system that will be called by the engine world with the function runSystem()
    struct DeathLife : public System {
        inline void run(World &world) override final
        {
            std::vector<std::shared_ptr<ecs::Entity>> joined = world.joinEntities<Life>();

            auto move = [](std::shared_ptr<ecs::Entity> entityPtr) {
                if (entityPtr.get()->getComponent<Life>().lifePoint <= 0)
                    entityPtr.get()->addComponent<Death>();
            };
            std::for_each(joined.begin(), joined.end(), move);
        }
    };
} // namespace ecs

#endif /* !DEATHLIFESYSTEM_HPP_ */
