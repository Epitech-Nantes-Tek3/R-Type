/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** Mouvement
*/

#ifndef MOUVEMENT_HPP_
#define MOUVEMENT_HPP_

#include <GameComponents/PositionComponent.hpp>
#include <GameComponents/VelocityComponent.hpp>
#include <World/World.hpp>
#include <algorithm>
#include <iostream>

namespace ecs
{
    /// @brief This is the Movement system. This system can move any entities which contains a Position and a Velocity
    /// Components It's a system that will be called by the engine world with the function runSystem()
    struct Movement : public System {
        void run(World &world) override final {}
    };
} // namespace ecs

#endif /* !MOUVEMENT_HPP_ */
