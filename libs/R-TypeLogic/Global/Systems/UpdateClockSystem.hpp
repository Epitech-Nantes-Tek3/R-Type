/*
** EPITECH PROJECT, 2022
** Project
** File description:
** UpdateClockSystem
*/

#ifndef UPDATECLOCKSYSTEM_HPP_
#define UPDATECLOCKSYSTEM_HPP_

#include "World/World.hpp"

namespace rtypelogic::global
{
    /// @brief UpdateClock System. Will be used to call the GameClock's reset
    struct UpdateClock : public ecs::System {
        /// @brief Run the UpdateClock System
        /// @param world The world where the clock will run
        void run(World &world) override final;
    };
}; // namespace rtypelogic::global

#endif /* !UPDATECLOCKSYSTEM_HPP_ */
