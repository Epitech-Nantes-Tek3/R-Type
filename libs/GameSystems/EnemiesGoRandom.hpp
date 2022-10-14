/*
** EPITECH PROJECT, 2022
** Rt-Type
** File description:
** EnemiesGoRandom
*/

#ifndef ENEMIESGORANDOM_HPP_
#define ENEMIESGORANDOM_HPP_

#include "GameComponents/DestinationComponent.hpp"
#include "GameComponents/EnemyComponent.hpp"
#include "GameComponents/PositionComponent.hpp"
#include "GameComponents/VelocityComponent.hpp"
#include "World/World.hpp"

namespace ecs
{
    /// @brief This is the GoRandom System for enemies.
    /// This system check if the enemy is at its destination, if so randomize a new one
    /// Otherwise compute a new velocity
    class EnemiesGoRandom : public System{
      public:
        /// @brief Run the GoRandom system
        /// @param world The world where the enemy will randomly move
        void run(World &world) override final;
    };
} // namespace ecs

#endif /* !ENEMIESGORANDOM_HPP_ */
