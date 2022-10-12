/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** DeathComponent
*/

#ifndef DEATHCOMPONENT_HPP_
#define DEATHCOMPONENT_HPP_

#include "Component/Component.hpp"

namespace ecs
{
    /// @brief The Death Class which defines that an entity is dead and will be deleted by Death System
    class Death : public Component {};
} // namespace ecs

#endif /* !DEATHCOMPONENT_HPP_ */
