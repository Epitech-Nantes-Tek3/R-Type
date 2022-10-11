/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** InvisibleComponent
*/

#ifndef INVISIBLECOMPONENT_HPP_
#define INVISIBLECOMPONENT_HPP_

#include "Component/Component.hpp"

namespace ecs
{
    /// @brief The Invisible component, to make an entity lives without drawing it
    class Invisible : public Component {};
} // namespace ecs

#endif /* !INVISIBLECOMPONENT_HPP_ */
