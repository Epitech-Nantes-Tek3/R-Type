/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** Resource
*/

#pragma once

#include <mutex>

namespace ecs
{
    /// @brief This is the Resource Class for ECS
    /// The base Resource type, all Resources must inherit from Resource.
    /// The std::mutex inheritance is in order to allow to lock a Resource when something wants to use/modify it.
    /// \/!\ When you want tu use/modify one already created Resource, you have to lock it. It is recommended to use
    /// std::lock_guard from boost.
    class Resource : public std::mutex {
      public:
        /// @brief This is the default destructor of Resource Class
        virtual ~Resource() = default;

        ///@brief Delete the copy constructor because a mutex can't be copied
        Resource(const Resource &) = delete;

      protected:
        /// @brief This is the constructor of Resource Class
        /// Because it can be used only by things that heritate from it
        Resource() = default;
    };
} // namespace ecs
