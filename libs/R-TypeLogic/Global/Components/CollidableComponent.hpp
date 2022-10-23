/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** CollidableComponent
*/

#ifndef COLLIDABLECOMPONENT_HPP_
#define COLLIDABLECOMPONENT_HPP_

#include "Component/Component.hpp"

namespace rtypelogic::global
{
    /// @brief The Collidable component, almost used for every entities
    class Collidable : public ecs::Component {};
} // namespace rtypelogic::global

#endif /* !COLLIDABLECOMPONENT_HPP_ */
