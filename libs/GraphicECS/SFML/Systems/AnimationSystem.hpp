/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** AnimationSystem
*/

#ifndef ANIMATIONSYSTEM_HPP_
#define ANIMATIONSYSTEM_HPP_

#include "System/System.hpp"
#include "World/World.hpp"

namespace graphicECS::SFML::Systems
{
    /// @brief This structure system updates the AnimationFrequency and update texture on shapes.
    struct AnimationSystem : public ecs::System {
        /// @brief It is used by the world to run this system. It updates textures on shapes and AnimationFrequency.
        /// @param world The corresponding world on which run this system.
        void run(World &world) override final;
    };
} // namespace graphicECS::SFML::Systems

#endif /* !ANIMATIONSYSTEM_HPP_ */
