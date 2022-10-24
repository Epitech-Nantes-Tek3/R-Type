/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** SendNewlyCreatedToServer
*/

#pragma once

#include "World/World.hpp"

namespace transisthor::ecslogic
{
    struct SendNewlyCreatedToServer : public ecs::System {
        /// @brief It sends the data of all the newly created entities to all the clients
        /// @param world The world which the system is running in.
        void runSystem(ecs::World &world);

        /// @brief It runs the system
        /// @param world The world which the system is running in.
        inline void run(ecs::World &world) override final { runSystem(world); };
    };
} // namespace transisthor::ecslogic
