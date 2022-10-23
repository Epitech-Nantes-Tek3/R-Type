/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** DeathLifeSystem
*/

#ifndef DEATHLIFESYSTEM_HPP_
#define DEATHLIFESYSTEM_HPP_

#include "World/World.hpp"
#include "R-TypeLogic/Global/Components/DeathComponent.hpp"
#include "R-TypeLogic/Global/Components/LifeComponent.hpp"

using namespace ecs;
namespace rtypelogic
{
    using namespace global;
    namespace server
    {
        /// @brief This is the DeathLife System.
        /// This System takes all entities that have a Life Component with 0 HP/life or less and adds a Death Component
        /// to them. It's a system that will be called by the engine world with the function runSystem()
        struct DeathLife : public System {
            inline void run(World &world) override final
            {
                std::vector<std::shared_ptr<ecs::Entity>> joined = world.joinEntities<Life>();

                auto deathlifetime = [](std::shared_ptr<ecs::Entity> entityPtr) {
                    if (entityPtr.get()->getComponent<Life>().lifePoint <= 0)
                        entityPtr.get()->addComponent<Death>();
                };
                std::for_each(joined.begin(), joined.end(), deathlifetime);
            }
        };
    } // namespace server
} // namespace rtypelogic

#endif /* !DEATHLIFESYSTEM_HPP_ */
