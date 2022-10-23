/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** BouncingComponent
*/

#ifndef BOUNCINGCOMPONENT_HPP_
#define BOUNCINGCOMPONENT_HPP_

#include "Component/Component.hpp"

namespace rtypelogic::global
{
    /// @brief The Bouncing component, to bounce projectiles after hitting one enemy
    class Bouncing : public ecs::Component {};
} // namespace rtypelogic::global

#endif /* !BOUNCINGCOMPONENT_HPP_ */
