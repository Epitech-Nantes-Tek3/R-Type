/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** ParallaxSystem
*/

#ifndef PARALLAXSYSTEM_HPP_
#define PARALLAXSYSTEM_HPP_

#include "System/System.hpp"
#include "World/World.hpp"

namespace graphicECS::SFML::Systems
{
    /// @brief Parallax System. Make a moving background to make an "infinite map"
    struct Parallax : public System {
      public:
        /// @brief Run the Parallax System
        /// @param world the world where the parallax will be executed
        void run(World &world) override final;
    };

} // namespace graphicECS::SFML::Systems

#endif /* !PARALLAXSYSTEM_HPP_ */
