/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** UpdateParallaxSystem
*/

#ifndef UPDATEPARALLAXSYSTEM_HPP_
#define UPDATEPARALLAXSYSTEM_HPP_

#include "World/World.hpp"

#define MIDDLE_BACKGROUND_TEXTURE_PATH "assets/Backgrounds/middle.png"
#define BACK_BACKGROUND_TEXTURE_PATH "assets/Backgrounds/back.png"
#define FAR_BACKGROUND_TEXTURE_PATH "assets/Backgrounds/far.png"

namespace graphicECS::SFML::Systems
{
    /// @brief Update the Parallax by changing backgrounds images depending on the game level resource
    struct UpdateParallax : public System {
      public:
        /// @brief Run the UpdateParallax system
        void run(World &world) override final;
    };
} // namespace graphicsECS::SFML::Systems

#endif /* !UPDATEPARALLAXSYSTEM_HPP_ */
