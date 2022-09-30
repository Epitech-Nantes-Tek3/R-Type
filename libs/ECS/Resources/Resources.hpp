/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** Resources
*/

#pragma once


namespace ecs
{
    /// @brief This is the Resource Class for ECS
    /// The base Resource type, all Resources must inherit from Resource.
    class Resource {
      public:
        /// @brief This is the destructor of Resource Class
        virtual ~Resource() = default;

      protected:
        /// @brief This is the constructor of Resource Class
        /// Because it can be use only by things that eritate by it
        Resource() = default;
    };
} // namespace ecs


