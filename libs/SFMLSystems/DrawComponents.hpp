/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** DrawComponents
*/

#ifndef DRAWCOMPONENTS_HPP_
#define DRAWCOMPONENTS_HPP_

#include "System/System.hpp"

namespace ecs
{
    /// @brief This class draw GraphicsComponents on window.
    struct DrawComponents : public System {
        void runSystem(World &world);
        /// @brief The run function of this system. It will be used by the world in the function runSystems.
        /// @param world The corresponding world on which run this system.
        inline void run(World &world) override final {runSystem(world);};
    };
} // namespace ecs

#endif /* !DRAWCOMPONENTS_HPP_ */
