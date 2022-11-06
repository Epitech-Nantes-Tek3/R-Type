/*
** EPITECH PROJECT, 2022
** Rt-Type
** File description:
** EnemiesPatterns
*/

#ifndef ENEMIESPATTERNS_HPP_
#define ENEMIESPATTERNS_HPP_

#include "World/World.hpp"
#include "R-TypeLogic/Global/Components/DestinationComponent.hpp"
#include "R-TypeLogic/Global/Components/EnemyComponent.hpp"
#include "R-TypeLogic/Global/Components/PositionComponent.hpp"
#include "R-TypeLogic/Global/Components/VelocityComponent.hpp"

namespace ecs
{
    /// @brief This is the pattern System for enemies.
    /// This system check if the enemy is at its destination, if so set a new destination based on enemy type
    /// Otherwise compute a new velocity
    class EnemiesPatterns : public System {
      public:
        /// @brief Run the patterns system
        /// @param world The world where the enemy will move
        void run(World &world) override final;
    };
} // namespace ecs

#endif /* !ENEMIESPATTERNS_HPP_ */
