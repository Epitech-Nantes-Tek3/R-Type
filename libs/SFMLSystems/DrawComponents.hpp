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
        /// @brief The run function of this system. It will be used by the world in the function runSystems.
        /// @param world The corresponding world on which run this system.
        void run(World &world) override final;
    };
} // namespace ecs

#endif /* !DRAWCOMPONENTS_HPP_ */
