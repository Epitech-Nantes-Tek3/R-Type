/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** World
*/

#pragma once

#include <concepts>
#include <cstddef>
#include <map>
#include <memory>
#include <mutex>
#include <typeindex>
#include <vector>
#include "Entity/Entity.hpp"
#include "Resource/Resource.hpp"
#include "System/System.hpp"
#include "Transisthor/Transisthor.hpp"
#include <unordered_map>

namespace transisthor_lib
{
    class Transisthor;
}

using namespace transisthor_lib;

namespace ecs
{
    class World final {
      public:
        /// @brief The ID type
        using ID = std::size_t;

        /// @brief This is the map of Entities in the World
        using EntitiesList = std::map<ID, std::shared_ptr<Entity>>;

        /// @brief This is the map of Resources of the World
        using ResourcesList = std::unordered_map<std::type_index, std::shared_ptr<Resource>>;

        /// @brief This is the map of Systems in the World
        using SystemsList = std::unordered_map<std::type_index, std::unique_ptr<System>>;

        ///@brief Construct a new World object
        ///@param id It's used to know what World is (example in a video game you can have a World(1) for pause menu and
        /// another World(2) for your game)
        inline World(ID id) : _id(id), _nextEntityId(1) { _transisthorBridge = std::shared_ptr<Transisthor>(nullptr); };

        ///@brief Get the object's ID
        ///@return ID of the World object
        inline ID getId() const { return _id; };

        ///@brief This function creates an Entity in the world
        ///@return Entity& reference to the created Entity
        Entity &addEntity();

        ///@brief Get the Entity object with the given id
        ///@param id Id of the searched Entity
        ///@return Entity& reference to the searched Entity
        ///@throw std::logic_error Throw an error if the entity does not exist
        Entity &getEntity(ID id) const;

        /// @brief It's a function which is used to update a component of an entity from a given distinctive component.
        /// @tparam DistinctiveC The component type which is used to disctinct the Entity
        /// @tparam C The component type of the component to update
        /// @param distinctive The component which is used to disctinct the Entity
        /// @param component The component of the component to update
        /// @return bool True if the coponent has been modified. False otherwise.
        template <std::derived_from<Component> DistinctiveC, std::derived_from<Component> C>
        bool updateComponentOfAnEntityFromGivenDistinctiveComponent(DistinctiveC distinctive, C component)
        {
            std::vector<std::shared_ptr<Entity>> joined = this->joinEntities<DistinctiveC>();

            for (std::shared_ptr<Entity> entityPtr : joined) {
                std::lock_guard(*entityPtr.get());
                DistinctiveC &dc = entityPtr->getComponent<DistinctiveC>();
                if (distinctive == dc) {
                    if (entityPtr->contains<C>()) {
                        C &old = entityPtr->getComponent<C>();
                        old = component;
                    } else {
                        entityPtr->addComponent<C>(component);
                    }
                    return true;
                }
            }
            return false;
        }

        ///@brief This function is used to join entities with the same components
        ///@tparam C Component types to search
        ///@param world The world to search in
        ///@return JoinedEntities A vector of all entities which have the given components
        template <std::derived_from<Component>... C> std::vector<std::shared_ptr<Entity>> joinEntities() const
        {
            std::vector<std::shared_ptr<Entity>> joinedEntities;

            for (auto &it : _entitiesList) {
                std::shared_ptr<Entity> entity = it.second;
                std::lock_guard(*entity.get());
                if (entity.get()->contains<C...>())
                    joinedEntities.push_back(entity);
            }
            return joinedEntities;
        }

        ///@brief Remove the Entity object with the given id
        ///@param id Id of the searched Entity
        ///@throw std::logic_error Throw an error if the entity does not exist
        void removeEntity(ID id);

        /// @brief This function can add a Resource to the World
        /// @tparam R Type of the Resource
        /// @tparam ...Args It allows to send multiple arguments (args)
        /// @param ...args All arguments which are used to construct the Resource
        /// @throw std::logic_error Throw an error if the Resource already exist
        /// @return &World A reference to itself
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
        /// @return The choosen Resource
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

        /// @brief This function will check if a group of Resource types (at least one Resource type) is in a World
        /// @tparam R1 First Resource type to check
        /// @tparam ...R2 OPTIONAL Next Resource type to check
        /// @return True if the group of Resource types is contained in the World. Otherwise False
        template <std::derived_from<Resource> R1, std::derived_from<Resource>... R2> bool containsResource() const
        {
            if (_resourcesList.count(typeid(R1)) == 0)
                return false;
            return containsResource<R2...>();
        }

        /// @brief This function will check if a group of System types (at least one System type) is in an World
        /// @tparam S1 First System type to check
        /// @tparam ...S2 OPTIONAL Next System type to check
        /// @return True if the group of System types is contained in the World. Otherwise False
        template <std::derived_from<System> S1, std::derived_from<System>... S2> bool containsSystem() const
        {
            if (_systemsList.count(typeid(S1)) == 0)
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

        /// @brief Set the bridge destination to a new transisthor
        /// @param transisthorBridge New bridge destination
        inline void setTransisthorBridge(std::shared_ptr<Transisthor> transisthorBridge)
        {
            _transisthorBridge = transisthorBridge;
        }

        ///@brief Get the Transisthor Bridge object
        ///@return std::shared_ptr<Transisthor>
        inline std::shared_ptr<Transisthor> getTransisthorBridge() { return _transisthorBridge; }

        ///@brief It runs all systems in the world
        void runSystems();

        ///@brief Destroy the World object
        ~World() = default;

      protected:
      private:
        ///@brief World's id
        ID _id;

        ///@brief ID of the next entity which will be created by the function addEntity()
        ID _nextEntityId;

        ///@brief Map of entities
        EntitiesList _entitiesList;

        /// @brief Map of Resources of the World Class
        ResourcesList _resourcesList;

        ///@brief Map of systems
        SystemsList _systemsList;

        /// @brief Bridge to the transisthor instance
        std::shared_ptr<Transisthor> _transisthorBridge;

        /// @brief This is the function which is called when none Resources types left
        /// @tparam ...R The last researched Resource
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
