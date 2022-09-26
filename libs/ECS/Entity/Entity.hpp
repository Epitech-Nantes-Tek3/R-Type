/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** Entity
*/

#pragma once

#include <concepts>
#include <cstddef>
#include <memory>
#include <typeindex>
#include <unordered_map>

#include "Components/Component.hpp"
#include "Entity/Entity.hpp"

/// @file libs/ECS/Entity/Entity.hpp

namespace ecs
{
    class Entity
    {
    public:
        /// The id type
        using Index = std::size_t;

        using ComponentsList = std::unordered_map<std::type_index, std::unique_ptr<Component>>;

        /// @returns The index of this entity.
        constexpr Index getId() const noexcept { return this->_id; }

        /// Entity index comparison.
        auto operator<=>(Entity const &other) const { return this->_id <=> other._id; }

        template <std::derived_from<Component> C, typename... Args>
        Entity &addComponent(Args &&...args)
        {
            // if already contains once -> throw ERROR

            this->_componentList[std::type_index(typeid(C))] = std::make_unique<C>(std::forward<Args>(args)...);
            return *this;
        }

        template <std::derived_from<Component> C>
        Component &getComponent() const
        {
            ComponentsList::iterator it = _componentList.find(std::type_index(typeid(C)));
            if (it == _componentList.end())
                throw std::logic_error("attempted to get a non-existent component");
            return *(it->second.get());
        }

        template <std::derived_from<Component> C>
        void removeComponent()
        {
            ComponentsList::iterator it = _componentList.find(std::type_index(typeid(C)));
            if (it == _componentList.end())
                throw std::logic_error("attempted to remove a non-existent component");
            _componentList.erase(it);
        }

        template <std::derived_from<Component>... C>
        bool contains(C... component) const
        {
            if (_componentList.find(std::type_index(typeid(component)...)) == _componentList.end())
                return false;
            return contains(component...);
        }

        inline constexpr bool contains() {return true;}

        ~Entity();

    private:
        Index _id;

        ComponentsList _componentList;

        inline constexpr Entity(Index id) : _id(id) {_componentList[std::type_index(typeid(Component))] = std::make_unique<Component>("Component");}
    };
}
