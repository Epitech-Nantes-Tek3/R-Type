/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** MobGenerationSystem
*/

#ifndef MOBGENERATIONSYSTEM_HPP_
#define MOBGENERATIONSYSTEM_HPP_

#include "World/World.hpp"

namespace ecs
{
    /// @brief This is the mob generation system
    /// It generates mob corresponding to the game level
    /// The difficulty increases with the game level
    struct MobGeneration : public System {
      public:
        /// @brief Run the Mob generation System
        /// @param world the world where the enemies will spawn
        void run(World &world) override final;
    };
} // namespace ecs

#endif /* !MOBGENERATIONSYSTEM_HPP_ */
