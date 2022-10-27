/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** RemoveAfkSystem
*/

#ifndef REMOVEAFKSYSTEM_HPP_
#define REMOVEAFKSYSTEM_HPP_

#include "World/World.hpp"

namespace ecs
{
    /// @brief This is the RemoveAfk System.
    /// It will send a protocol 13 to afk client
    struct RemoveAfkSystem : public System {
        /// @brief Run function for the RemoveAfk System
        /// @param world The world where the Afk Frequency Component will be used.
        void run(World &world) override final;
    };
} // namespace ecs

#endif /* !REMOVEAFKSYSTEM_HPP_ */
