/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** Mouvement
*/

#ifndef MOUVEMENT_HPP_
#define MOUVEMENT_HPP_

#include "World/World.hpp"
#include "R-TypeLogic/Global/Components/PositionComponent.hpp"
#include "R-TypeLogic/Global/Components/VelocityComponent.hpp"

namespace rtypelogic::global
{
    /// @brief This is the Movement system. This system can move any entities which contains a Position and a Velocity
    /// Component. It's a system that will be called by the engine world with the function runSystem()
    struct Movement : public ecs::System {
        /// @brief Run the Movement System
        /// @param world The world where the entities will move
        void run(World &world) override final;
    };
} // namespace rtypelogic::global

#endif /* !MOUVEMENT_HPP_ */
