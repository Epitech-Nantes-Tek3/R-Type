/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** SoundManagement
*/

#ifndef SOUNDMANAGEMENT_HPP_
#define SOUNDMANAGEMENT_HPP_

#include "System/System.hpp"
#include "World/World.hpp"
#include "GraphicECS/SFML/Components/SoundComponent.hpp"

namespace graphicECS::SFML::Systems
{
    struct SoundManagement : public ecs::System {
        /// @brief The run function of this system. It will be used by the world in the function runSystems.
        /// @param world The corresponding world on which run this system.
        void run(World &world);
    };
} // namespace graphicECS::SFML::Systems
#endif /* !SOUNDMANAGEMENT_HPP_ */
