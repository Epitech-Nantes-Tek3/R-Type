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

    /// All systems must inherit from System.
    /// A system is used to do any interactions you want on all components you want
    class System {
      public:
        virtual ~System() = default;

        /// The main function which implements the desired logic.
        virtual void run(World &world) = 0;
    };
} // namespace ecs
