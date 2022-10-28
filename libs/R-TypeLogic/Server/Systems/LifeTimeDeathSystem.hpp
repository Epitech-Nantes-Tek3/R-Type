/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** LifeTimeDeathSystem
*/

#ifndef LIFETIMEDEATH_SYSTEM_HPP_
#define LIFETIMEDEATH_SYSTEM_HPP_

#include <mutex>
#include "World/World.hpp"
#include "R-TypeLogic/Global/Components/DeathComponent.hpp"
#include "R-TypeLogic/Global/Components/LifeTimeComponent.hpp"

namespace ecs
{
    /// @brief This is the LifeTimeDeath System.
    /// This System takes all entities that have a LifeTime Component with 0 timeLeft or less and adds a Death Component
    /// to them. It's a system that will be called by the engine world with the function runSystem()
    struct LifeTimeDeath : public System {
        inline void run(World &world) override final
        {
            std::vector<std::shared_ptr<ecs::Entity>> joined = world.joinEntities<LifeTime>();

            auto deathLifeTime = [](std::shared_ptr<ecs::Entity> entityPtr) {
                std::lock_guard(*entityPtr.get());
                if (entityPtr.get()->getComponent<LifeTime>().timeLeft <= std::chrono::duration<double>(0.0)
                    && !entityPtr.get()->contains<Death>()) {
                    entityPtr.get()->addComponent<Death>();
                }
            };
            std::for_each(joined.begin(), joined.end(), deathLifeTime);
        }
    };
} // namespace ecs

#endif /* !LifeTimeDeathSYSTEM_HPP_ */
