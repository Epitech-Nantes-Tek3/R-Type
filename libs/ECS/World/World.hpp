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

        /// @brief This function can get a Resource in the World
        /// @tparam C Search Resource
        /// @throw std::logic_error Throw an error if the Resource does not exists
        /// @return The Resource choosen
        template <std::derived_from<Resource> C> C &getResource() const
        {
            if (_resourceList.count(typeid(C)) == 0)
                throw std::logic_error("attempted to get a non-existent Resource");
            return static_cast<C &>(*(_resourceList.at(typeid(C)).get()));
        }

        /// @brief Remove a Resource of the world
        /// @tparam C The choosen Resource to remove
        /// @throw std::logic_error Throw an error if the Resource does not exists
        template <std::derived_from<Resource> C> void removeResource()
        {
            ResourcesList::iterator it = _resourceList.find(typeid(C));
            if (it == _resourceList.end())
                throw std::logic_error("attempted to remove a non-existent Resource");
            _resourceList.erase(it);
        }

      protected:

      private:

        /// @brief List of Resources of the World Class
        ResourcesList _resourceList;
    };
} // namespace ecs
