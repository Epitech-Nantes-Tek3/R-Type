/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** NoAfkInMenuSystem
*/

#ifndef NOAFKINMENUSYSTEM_HPP_
#define NOAFKINMENUSYSTEM_HPP_

#include <chrono>
#include "World/World.hpp"

namespace ecs
{
    /// @brief This is a system which makes the player "connected" to still have the client open while in menu
    struct NoAfkInMenu : public System {
        /// @brief Run the NoAfkInMenu System
        /// @param world The world where the player's client is
        void run(World &world) override final;
    };
} // namespace ecs

#endif /* !NOAFKINMENUSYSTEM_HPP_ */
