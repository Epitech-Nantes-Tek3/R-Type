/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** InvinsibleComponent
*/

#ifndef INVINSIBLECOMPONENT_HPP_
#define INVINSIBLECOMPONENT_HPP_

#include "Component/Component.hpp"

namespace ecs
{
    /// @brief The Invinsible component, to nullify all damages
    /// It's a networkable component.
    class Invinsible : public Component {};
} // namespace ecs

#endif /* !INVINSIBLECOMPONENT_HPP_ */
