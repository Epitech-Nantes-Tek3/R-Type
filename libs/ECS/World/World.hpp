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
#include "System/System.hpp"

namespace ecs
{
    class World final {
      public:
        /// @brief The id type
        using Index = std::size_t;

        /// @brief This is the map of Entities in the World
        using EntitiesList = std::map<Index, std::unique_ptr<Entity>>;

        /// @brief This is the map of Resource of the World
        using ResourcesList = std::unordered_map<std::type_index, std::unique_ptr<Resource>>;

        /// @brief This is the map of the Systems in the World
        using SystemsList = std::unordered_map<std::type_index, std::unique_ptr<System>>;

        ///@brief Construct a new World object
        ///@param id Id of the searched Entity
        inline World(Index id) : _id(id), _nextEntityId(0) {};

        ///@brief Get the Id object
        ///@return Index
        inline Index getId() {return _id;} const;

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

        /// @brief This function can add a Resource to the World
        /// @tparam R Type of the Resource
        /// @tparam ...Args This allows to send multiple arguments (args)
        /// @param ...args All arguments which are used to construct the Resource
        /// @throw std::logic_error Throw an error if the Resource already exists
        /// @return itself
        template <std::derived_from<Resource> R, typename... Args> World &addResource(Args &&...args)
        {
            if (contains<R>())
                throw std::logic_error("attempted to add a Resource that already exists");
            this->_resourcesList[std::type_index(typeid(R))] = std::make_unique<R>(std::forward<Args>(args)...);
            return *this;
        }

        /// @brief This function can get a Resource in the World
        /// @tparam R Search Resource
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
        /// @throw std::logic_error Throw an error if the Resource does not exists
        template <std::derived_from<Resource> R> void removeResource()
        {
            ResourcesList::iterator it = _resourcesList.find(typeid(R));
            if (it == _resourcesList.end())
                throw std::logic_error("attempted to remove a non-existent Resource");
            _resourcesList.erase(it);
        }

        /// @brief This function will check if a group of Resources types (at least one Resource type) is in an World
        /// @tparam R1 First Resource type to check
        /// @tparam ...R2 OPTIONAL Next Resource type to check
        /// @return True if the group of Resource types is contained in the World. Otherwise False
        template <std::derived_from<Resource> R1, std::derived_from<Resource>... R2> bool contains() const
        {
            if (_resourcesList.count(typeid(R1)) == 0)
                return false;
            return contains<R2...>();
        }

        /// @brief This function can add a System to the World
        /// @tparam S Type of the System
        /// @throw std::logic_error Throw an error if the System already exists
        /// @return itself
        template <std::derived_from<System> S> World &addSystem()
        {
            if (contains<S>())
                throw std::logic_error("attempted to add a System that already exists");
            this->_systemsList[std::type_index(typeid(S))] = std::make_unique<S>();
            return *this;
        }

        void runSystems()
        {
            for (auto& it: _systemsList)
                it.second.get()->run();
        }

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
        requires(sizeof...(R) == 0) bool contains() const { return true; }
    };
} // namespace ecs
