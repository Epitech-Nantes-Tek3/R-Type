/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** DeathLifeTimeSystem
*/

#ifndef DEATHLIFETIMESYSTEM_HPP_
#define DEATHLIFETIMESYSTEM_HPP_

#include "World/World.hpp"
#include "GameComponents/LifeTimeComponent.hpp"
#include "GameComponents/DeathComponent.hpp"

namespace ecs
{
    /// @brief This is the DeathLifeTime Component. This Component take all entities which have LifeTime
    /// Component with 0 or under life and add Death Component to it. It's a system that will be called
    /// by the engine world with the function runSystem()
    struct DeathLifeTime : public System {
        inline void run(World &world) override final
        {
            std::vector<std::shared_ptr<ecs::Entity>> joined = world.joinEntities<Lifetime>();



            auto move = [](std::shared_ptr<ecs::Entity> entityPtr) {
                if (entityPtr.get()->getComponent<Lifetime>().timeLeft <= std::chrono::duration<double>(0.0))
                    entityPtr.get()->addComponent<Death>();
            };
            std::for_each(joined.begin(), joined.end(), move);
        }
    };
} // namespace ecs

#endif /* !DEATHLIFETIMESYSTEM_HPP_ */