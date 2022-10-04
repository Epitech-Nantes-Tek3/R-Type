/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** System
*/

#pragma once

/// @file libs/ECS/System.hpp

namespace ecs
{
    /// The World which contains the system. World Class is in World.hpp
    class World;

    /// The base system type, all systems must inherit from System.
    class System {
      public:
        virtual ~System() = default;

        /// Run the system.
        virtual void run(World &world) = 0;
    };
} // namespace ecs
