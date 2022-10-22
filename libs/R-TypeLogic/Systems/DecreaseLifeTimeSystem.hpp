/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** DecreaseLifeTimeSystem
*/

#ifndef DECREASELIFETIMESYSTEM_HPP_
#define DECREASELIFETIMESYSTEM_HPP_

#include "World/World.hpp"
#include "R-TypeLogic/Components/DeathComponent.hpp"
#include "R-TypeLogic/Components/LifeTimeComponent.hpp"
#include "R-TypeLogic/SharedResources/GameClock.hpp"

namespace ecs
{
    /// @brief This is the DecreaseLifeTime System. This System decrease LifeTime Component at every tick.
    /// It's a system that will be called by the engine world with the function runSystem()
    struct DecreaseLifeTime : public System {
        inline void run(World &world) override final
        {
            std::vector<std::shared_ptr<ecs::Entity>> joined = world.joinEntities<LifeTime>();

            auto decreaseLifeTime = [&world](std::shared_ptr<ecs::Entity> entityPtr) {
                entityPtr.get()->getComponent<LifeTime>() = entityPtr.get()->getComponent<LifeTime>().timeLeft
                    - std::chrono::duration<double>(world.getResource<GameClock>().getElapsedTime());
            };
            std::for_each(joined.begin(), joined.end(), decreaseLifeTime);
        }
    };
} // namespace ecs

#endif /* !DECREASELIFETIMESYSTEM_HPP_ */
