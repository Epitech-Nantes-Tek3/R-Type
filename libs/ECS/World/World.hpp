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
#include <map>
#include <memory>
#include <typeindex>
#include <vector>
#include "Entity/Entity.hpp"
#include "Resource/Resource.hpp"
#include "System/System.hpp"
#include <unordered_map>

namespace ecs
{
    class World final {
      public:
        /// @brief The id type
        using Index = std::size_t;

        /// @brief This is the map of Entities in the World
        using EntitiesList = std::map<Index, std::shared_ptr<Entity>>;

        /// @brief This is the map of Resource of the World
        using ResourcesList = std::unordered_map<std::type_index, std::shared_ptr<Resource>>;

        /// @brief This is the map of the Systems in the World
        using SystemsList = std::unordered_map<std::type_index, std::unique_ptr<System>>;

        ///@brief Construct a new World object
        ///@param id Id of the searched Entity
        inline World(Index id) : _id(id), _nextEntityId(1){};

        ///@brief Get the Id object
        ///@return Index
        inline Index getId() const { return _id; };

        ///@brief This function create an Entity in the world
        ///@return Entity& reference to the created Entity
        Entity &addEntity();

        ///@brief Get the Entity object with the given id
        ///@param id Id of the searched Entity
        ///@return Entity& reference to the searched Entity
        ///@throw std::logic_error Throw an error if the entity does not exist
        Entity &getEntity(Index id) const;

        ///@brief This function is used to join entities with the same component
        ///@tparam C Component types
        ///@param world The world to search in
        ///@return JoinedEntities A vector of all entities which have the given components
        template <std::derived_from<Component>... C> std::vector<std::shared_ptr<Entity>> joinEntities() const
        {
            std::vector<std::shared_ptr<Entity>> joinedEntities;

            for (auto &it : _entitiesList) {
                std::shared_ptr<Entity> entity = it.second;
                if (entity.get()->contains<C...>())
                    joinedEntities.push_back(entity);
            }
            return joinedEntities;
        }

        ///@brief Remove the Entity object with the given id
        ///@param id Id of the searched Entity
        ///@throw std::logic_error Throw an error if the entity does not exist
        void removeEntity(Index id);

        /// @brief This function can add a Resource in the World
        /// @tparam R Type of the Resource
        /// @tparam ...Args This allow to send multiple arguments (args)
        /// @param ...args All arguments which are used to construct the Resource
        /// @throw std::logic_error Throw an error if the Resource already exists
        /// @return It return itself
        template <std::derived_from<Resource> R, typename... Args> World &addResource(Args &&...args)
        {
            if (containsResource<R>())
                throw std::logic_error("attempted to add a Resource that already exists");
            this->_resourcesList[std::type_index(typeid(R))] = std::make_shared<R>(std::forward<Args>(args)...);
            return *this;
        }

        /// @brief This function can get a Resource in the World
        /// @tparam R Searched Resource
        /// @throw std::logic_error Throw an error if the Resource does not exists
        /// @return The Resource choosen
        template <std::derived_from<Resource> R> R &getResource() const
        {
            if (_resourcesList.count(typeid(R)) == 0)
                throw std::logic_error("attempted to get a non-existent Resource");
            return static_cast<R &>(*(_resourcesList.at(typeid(R)).get()));
        }

        /// @brief Remove a Resource of the world
        /// @tparam R The choosen Resource to remove
        /// @throw std::logic_error Throw an error if the Resource does not exist
        template <std::derived_from<Resource> R> void removeResource()
        {
            ResourcesList::iterator it = _resourcesList.find(typeid(R));
            if (it == _resourcesList.end())
                throw std::logic_error("attempted to remove a non-existent Resource");
            _resourcesList.erase(it);
        }

        /// @brief This function will check if a group of Resources types (at least one Resource type) is in a World
        /// @tparam R1 First Resource type to check
        /// @tparam ...R2 OPTIONAL Next Resource type to check
        /// @return True if the group of Resource types is contained in the World. Otherwise False
        template <std::derived_from<Resource> R1, std::derived_from<Resource>... R2> bool containsResource() const
        {
            if (_resourcesList.count(typeid(R1)) == 0)
                return false;
            return containsResource<R2...>();
        }

        /// @brief This function will check if a group of Systems types (at least one System type) is in an World
        /// @tparam S1 First System type to check
        /// @tparam ...S2 OPTIONAL Next System type to check
        /// @return True if the group of System types is contained in the World. Otherwise False
        template <std::derived_from<System> S1, std::derived_from<System>... S2> bool containsSystem() const
        {
            if (_resourcesList.count(typeid(S1)) == 0)
                return false;
            return containsSystem<S2...>();
        }

        /// @brief This function can add a System to the World
        /// @tparam S Type of the System
        /// @throw std::logic_error Throw an error if the System already exists
        /// @return itself
        template <std::derived_from<System> S> World &addSystem()
        {
            if (containsSystem<S>())
                throw std::logic_error("attempted to add a System that already exists");
            this->_systemsList[std::type_index(typeid(S))] = std::make_unique<S>();
            return *this;
        }

        ///@brief It runs all systems in the world
        void runSystems();

        ///@brief Destroy the World object
        ~World() = default;

      protected:
      private:
        ///@brief World's id
        Index _id;

        ///@brief index of the next entity which will be created by the function addEntity()
        Index _nextEntityId;

        ///@brief Map of entities
        EntitiesList _entitiesList;

        /// @brief List of Resources of the World Class
        ResourcesList _resourcesList;

        ///@brief Map of systems
        SystemsList _systemsList;

        /// @brief This is the function which is called when none Resources types left
        /// @tparam ...R The last research Resource
        /// @return True
        template <std::derived_from<Resource>... R>
        requires(sizeof...(R) == 0) bool containsResource() const { return true; }

        /// @brief This is the function which is called when none Systems types left
        /// @tparam ...S The last research System
        /// @return True
        template <std::derived_from<System>... S>
        requires(sizeof...(S) == 0) bool containsSystem() const { return true; }
    };
} // namespace ecs
