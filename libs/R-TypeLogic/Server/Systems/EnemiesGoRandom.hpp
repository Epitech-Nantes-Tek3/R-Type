/*
** EPITECH PROJECT, 2022
** Rt-Type
** File description:
** EnemiesGoRandom
*/

#ifndef ENEMIESGORANDOM_HPP_
#define ENEMIESGORANDOM_HPP_

#include "World/World.hpp"
#include "R-TypeLogic/Global/Components/DestinationComponent.hpp"
#include "R-TypeLogic/Global/Components/EnemyComponent.hpp"
#include "R-TypeLogic/Global/Components/PositionComponent.hpp"
#include "R-TypeLogic/Global/Components/VelocityComponent.hpp"

namespace ecs
{
    /// @brief This is the GoRandom System for enemies.
    /// This system check if the enemy is at its destination, if so randomize a new one
    /// Otherwise compute a new velocity
    class EnemiesGoRandom : public System {
      public:
        /// @brief Run the GoRandom system
        /// @param world The world where the enemy will randomly move
        void run(World &world) override final;
    };
} // namespace ecs

#endif /* !ENEMIESGORANDOM_HPP_ */
