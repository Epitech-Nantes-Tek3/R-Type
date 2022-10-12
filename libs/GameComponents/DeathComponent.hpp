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
    /// @brief The Death class, defining if an entity is dead. If an Entity has it's component, it's destroyed by the system DeathSystem
    class Death : public Component {};
} // namespace ecs

#endif /* !DEATHCOMPONENT_HPP_ */
