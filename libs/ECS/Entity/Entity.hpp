/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** Entity
*/

#pragma once

#include <concepts>
#include <cstddef>
#include <iostream>
#include <memory>
#include <mutex>
#include <typeindex>
#include <unordered_map>

#include "Component/Component.hpp"

namespace ecs
{
    /// @brief This is the Entity Class for E.C.S.
    /// It stores the related Components
    /// The std::mutex inheritance is in order to allows to lock an Entity when something wants to use/modifie it
    class Entity final : public std::mutex {
      public:
        /// @brief The id type
        using ID = std::size_t;

        /// @brief This is the map of Components of the Entity
        using ComponentsList = std::unordered_map<std::type_index, std::unique_ptr<Component>>;

        /// @brief This function can return the Id of itself
        /// @returns The index of this entity.
        inline constexpr ID getId() const noexcept { return this->_id; }

        /// @brief This function can add a Component to the Entity
        /// @tparam C Type of the component
        /// @tparam ...Args This allows to send multiple arguments (args)
        /// @param ...args All arguments which are used to construct the Component
        /// @throw std::logic_error Throw an error if the component already exists
        /// @return Entity& a reference to itself
        template <std::derived_from<Component> C, typename... Args> Entity &addComponent(Args &&...args)
        {
            if (contains<C>())
                throw std::logic_error("attempted to add component that already exists");
            this->_componentList[std::type_index(typeid(C))] = std::make_unique<C>(std::forward<Args>(args)...);
            return *this;
        }

        /// @brief This function can get a Component in the Entity
        /// @tparam C Searched component type
        /// @throw std::logic_error Throw an error if the component does not exists
        /// @return The choosen composent
        template <std::derived_from<Component> C> C &getComponent() const
        {
            if (_componentList.count(typeid(C)) == 0)
                throw std::logic_error("attempted to get a non-existent component");
            return static_cast<C &>(*(_componentList.at(typeid(C)).get()));
        }

        /// @brief Remove a Component of the Entity
        /// @tparam C The choosen component type to remove
        /// @throw std::logic_error Throw an error if the component does not exist
        template <std::derived_from<Component> C> void removeComponent()
        {
            ComponentsList::iterator it = _componentList.find(typeid(C));
            if (it == _componentList.end())
                throw std::logic_error("attempted to remove a non-existent component");
            _componentList.erase(it);
        }

        /// @brief This function will check if a group of Component types (at least one Component type) is in an Entity
        /// @tparam C1 First Component type to check
        /// @tparam ...C2 OPTIONAL Next Component type to check
        /// @return True if the group of Component types is contained in Entity. Otherwise False
        template <std::derived_from<Component> C1, std::derived_from<Component>... C2> bool contains() const
        {
            if (_componentList.count(typeid(C1)) == 0)
                return false;
            return contains<C2...>();
        }

        /// @brief Default destructor. This is the destructor of the Entity Class
        ~Entity() = default;

        /// @brief This is the constructor of the Entity Class
        /// @param id The id of the Entity
        inline Entity(ID id) : _id(id), _componentList() {}

        ///@brief Delete the copy constructor because a mutex can't be copied
        Entity(const Entity &) = delete;

      private:
        /// @brief Id of the Entity Class
        ID _id;

        /// @brief List of Components of the Entity Class
        ComponentsList _componentList;

        /// @brief This is the function which is called when none Component types left
        /// @tparam ...C The last research Component
        /// @return True
        template <std::derived_from<Component>... C>
        requires(sizeof...(C) == 0) bool contains() const { return true; }
    };

    /// @brief Will check if First Entity ID is equal to Second Entity ID. Overide of == operator
    /// @param entity First Entity
    /// @param other Second Entity
    /// @return True if both Entity are same
    inline auto operator==(Entity const &entity, Entity const &other) { return entity.getId() == other.getId(); }

    /// @brief Will check if First Entity ID is different to Second Entity ID. Overide of != operator
    /// @param entity First Entity
    /// @param other Second Entity
    /// @return True if both Entity are different
    inline auto operator!=(Entity const &entity, Entity const &other) { return entity.getId() != other.getId(); }

} // namespace ecs
