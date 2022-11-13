/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** UpdateBackgroundMusic
*/

#ifndef UPDATEBACKGROUNDMUSIC_HPP_
#define UPDATEBACKGROUNDMUSIC_HPP_

#include "World/World.hpp"
#include "maccro.h"

namespace graphicECS::SFML::Systems
{
    /// @brief Update the music depending on the current level
    struct UpdateBackgroundMusic : public System {
      public:
        /// @brief Run the Update Background system
        /// @param world world where the music will be changed
        void run(World &world) override final;
    };
} // namespace graphicECS::SFML::Systems

#endif /* !UPDATEBACKGROUNDMUSIC_HPP_ */
