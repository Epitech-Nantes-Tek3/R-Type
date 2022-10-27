/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** DisconnectableSystem
*/

#ifndef DISCONNECTABLESYSTEM_HPP_
#define DISCONNECTABLESYSTEM_HPP_

#include "World/World.hpp"

namespace ecs
{
    /// @brief This is the Disconnectable System.
    /// It will add the disconnectableSystem component to all the associated entity.
    struct DisconnectableSystem : public System {
        /// @brief Run function for the Disconnectable System
        /// @param world The world where the disconnectableComponent will be used.
        void run(World &world) override final;
    };
} // namespace ecs

#endif /* !COLLIDABLESYSTEM_HPP_ */
