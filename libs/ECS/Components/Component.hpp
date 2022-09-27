/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** Component
*/

#pragma once

#include <string>

/// @file libs/ECS/Entity/Entity.hpp

namespace ecs
{
    class Component
    {
    public:

        /// @brief This is the destructor of Component Class
        virtual ~Component() = default;

    protected:
        Component() = default;
    };
}
