/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** AnimationSystem
*/

#ifndef ANIMATIONSYSTEM_HPP_
#define ANIMATIONSYSTEM_HPP_

#include "System/System.hpp"

namespace ecs
{
    struct AnimationSystem : public System {
        void run(World &world) override final;
    };
} // namespace ecs

#endif /* !ANIMATIONSYSTEM_HPP_ */
