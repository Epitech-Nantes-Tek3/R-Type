/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** EnemyComponent
*/

#ifndef ENEMYCOMPONENT_HPP_
#define ENEMYCOMPONENT_HPP_

#include "Component/Component.hpp"

namespace rtypelogic::global
{
    /// @brief Enemy Component allows an entity to be used as an Enemy
    class Enemy : public ecs::Component {};
} // namespace rtypelogic::global

#endif /* !ENEMYCOMPONENT_HPP_ */
