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
    struct AnimationSystem : public ecs::System {
        void run(World &world) override final;
    };
} // namespace graphicECS::SFML::Systems

#endif /* !ANIMATIONSYSTEM_HPP_ */
