/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** EnemyShootSystem
*/

#ifndef ENEMYSHOOTSYSTEM_HPP_
#define ENEMYSHOOTSYSTEM_HPP_

#include "World/World.hpp"

namespace ecs
{
    /// @brief The Enemy shoot system
    /// This system create a enemyProjectile each time the cooldown is equal to zero
    class EnemyShootSystem : public System {
      /// @brief Run the system Enemy shoot
      /// @param world The world where the enemies will shoot
      void run(World &world) override final;
    };
} // namespace ecs

#endif /* !ENEMYSHOOTSYSTEM_HPP_ */
