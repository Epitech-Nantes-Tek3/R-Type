/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** UpdateLifeTextSystem
*/

#ifndef UPDATELIFETEXTSYSTEM_HPP_
#define UPDATELIFETEXTSYSTEM_HPP_

#include "System/System.hpp"
#include "World/World.hpp"

namespace graphicECS::SFML::Systems
{
    /// @brief This structure system updates the Text Life.
    struct UpdateLifeTextSystem : public ecs::System {
        /// @brief It is used by the world to run this system. It updates Life Text.
        /// @param world The corresponding world on which run this system.
        void run(World &world) override final;
    };
} // namespace graphicECS::SFML::Systems

#endif /* !UPDATELIFETEXTSYSTEM_HPP_ */
