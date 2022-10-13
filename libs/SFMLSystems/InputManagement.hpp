/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** InputManagement
*/

#ifndef INPUTMANAGEMENT_HPP_
#define INPUTMANAGEMENT_HPP_

#include "System/System.hpp"
#include "World/World.hpp"

namespace ecs
{
    /// @brief This system class manage SFML input to link them to an action.
    struct InputManagement : public System {
        void runSystem(World &world);
        /// @brief The run function of this system. It will be used by the world in the function runSystems.
        /// @param world The corresponding world on which run this system.
        inline void run(World &world) override final {runSystem(world);};
    };
} // namespace

#endif /* !INPUTMANAGEMENT_HPP_ */
