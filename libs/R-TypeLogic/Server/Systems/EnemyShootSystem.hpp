/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** EnemyShootSystem
*/

#ifndef ENEMYSHOOTSYSTEM_HPP_
#define ENEMYSHOOTSYSTEM_HPP_

#include "World/World.hpp"

namespace rtypelogic
{
    namespace server
    {
        /// @brief The Enemy shoot system
        /// This system create a enemyProjectile each time the cooldown is equal to zero
        class EnemyShootSystem : public ecs::System {
            /// @brief Run the system Enemy shoot
            /// @param world The world where the enemies will shoot
            void run(ecs::World &world) override final;
        };
    } // namespace server
} // namespace rtypelogic

#endif /* !ENEMYSHOOTSYSTEM_HPP_ */
