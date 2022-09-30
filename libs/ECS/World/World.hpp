/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** World
*/

#pragma once

#include <concepts>
#include <cstddef>
#include <iostream>
#include <memory>
#include <typeindex>
#include <unordered_map>
#include <map>
#include "Entity/Entity.hpp"

#include "Resource/Resource.hpp"

namespace ecs
{
    class World final {
      public:
        /// @brief The id type
        using Index = std::size_t;

        /// @brief This is the map of Entities in the World
        using EntitiesList = std::map<Index, std::unique_ptr<Entity>>;

        /// @brief This is the tab of Resource of the World
        using ResourcesList = std::unordered_map<std::type_index, std::unique_ptr<Resource>>;

        ///@brief Get the Id object
        ///@return Index
        inline Index getId() {return _id;};

        ///@brief This function create an Entity in the world
        ///@return Entity& reference to the created Entity
        Entity &addEntity();

        ///@brief Get the Entity object with the given id
        ///@param id Id of the searched Entity
        ///@return Entity& reference to the searched Entity
        ///@throw std::logic_error Throw an error if the entity does not exists
        Entity &getEntity(Index id) const;

        ///@brief Remove the Entity object with the given id
        ///@param id Id of the searched Entity
        ///@throw std::logic_error Throw an error if the entity does not exists
        void removeEntity(Index id);

        ///@brief Construct a new World object
        ///@param id Id of the searched Entity
        inline World(Index id) : _id(id), _entitiesList(), _nextEntityId(0){};

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

        /// @brief This function can add a Resource to the World
        /// @tparam C Type of the Resource
        /// @tparam ...Args This allows to send multiple arguments (args)
        /// @param ...args All arguments which are used to construct the Resource
        /// @throw std::logic_error Throw an error if the Resource already exists
        /// @return itself
        template <std::derived_from<Resource> C, typename... Args> World &addResource(Args &&...args)
        {
            if (contains<C>())
                throw std::logic_error("attempted to add Resource that already exists");
            this->_resourceList[std::type_index(typeid(C))] = std::make_unique<C>(std::forward<Args>(args)...);
            return *this;
        }

        /// @brief This function will check if a group of Resources types (at least one Resource type) is in an World
        /// @tparam C1 First Resource type to check
        /// @tparam ...C2 OPTIONAL Next Resource type to check
        /// @return True if the group of Resource types is contained in the World. Otherwise False
        template <std::derived_from<Resource> C1, std::derived_from<Resource>... C2> bool contains() const
        {
            if (_resourceList.count(typeid(C1)) == 0)
                return false;
            return contains<C2...>();
        }
        ///@brief Destroy the World object
        ~World() = default;

      protected:
      private:
        /// @brief This is the function which is called when none Resources types left
        /// @tparam ...C The last research Resource
        /// @return True
        template <std::derived_from<Resource>... C>
        requires(sizeof...(C) == 0) bool contains() const { return true; }
        ///@brief World's id
        Index _id;

        ///@brief Map of entities
        EntitiesList _entitiesList;

        ///@brief index of the next entity which will be created by the function addEntity()
        Index _nextEntityId;

        /// @brief List of Resources of the World Class
        ResourcesList _resourceList;
    };
} // namespace ecs
