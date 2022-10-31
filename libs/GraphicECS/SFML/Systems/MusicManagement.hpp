/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** MusicManagement
*/

#ifndef MUSICMANAGEMENT_HPP_
#define MUSICMANAGEMENT_HPP_

#include "System/System.hpp"
#include "World/World.hpp"
#include "GraphicECS/SFML/Components/MusicComponent.hpp"

namespace graphicECS::SFML::Systems
{
    struct MusicManagement : public System {
      public:
        /// @brief The run function of this system. It will be used by the world in the function runSystems.
        /// @param world The corresponding world on which run this system.
        void run(World &world);
    };
} // namespace graphicECS::SFML::Systems
#endif /* !MUSICMANAGEMENT_HPP_ */
