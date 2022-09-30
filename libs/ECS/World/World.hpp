/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** World
*/

#pragma once

#include "Resources/Resources.hpp"

namespace ecs
{
    class World {
      public:
        /// @brief This is the tab of Resource of the World
        using ResourcesList = std::unordered_map<std::type_index, std::unique_ptr<Resource>>;

        World();
        ~World();

      protected:

      private:

        /// @brief List of Resources of the World Class
        ResourcesList _resourceList;
    };
} // namespace ecs
