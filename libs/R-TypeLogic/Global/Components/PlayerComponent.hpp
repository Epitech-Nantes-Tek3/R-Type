/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** PlayerComponent
*/

#ifndef PLAYERCOMPONENT_HPP_
#define PLAYERCOMPONENT_HPP_

#include "Component/Component.hpp"

namespace rtypelogic::global
{
    /// @brief Player Component allows an entity to be used as a Player
    class Player : public ecs::Component {};
} // namespace rtypelogic::global

#endif /* !PLAYERCOMPONENT_HPP_ */
