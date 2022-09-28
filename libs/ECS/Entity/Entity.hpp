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

        template <std::derived_from<Component> C, typename... Args>
        Entity &addComponent(Args &&...args)
        {
            // if already contains once -> throw ERROR

            this->_componentList[std::type_index(typeid(C))] = std::make_unique<C>(std::forward<Args>(args)...);
            return *this;
        }

        template <std::derived_from<Component> C>
        C &getComponent() const
        {
            if (_componentList.count(typeid(C)) == 0)
                throw std::logic_error("attempted to get a non-existent component");
            return static_cast<C&>(*(_componentList.at(typeid(C)).get()));
        }

        template <std::derived_from<Component> C>
        void removeComponent()
        {
            ComponentsList::iterator it = _componentList.find(typeid(C));
            if (it == _componentList.end())
                throw std::logic_error("attempted to remove a non-existent component");
            _componentList.erase(it);
        }

        template <std::derived_from<Component>... C>
        bool contains(C... component) const
        {
            if (_componentList.count(typeid(component)...) == 0)
                return false;
            return contains(component...);
        }

        inline constexpr bool contains() {return true;}

        ~Entity() = default;

        inline Entity(Index id) : _id(id), _componentList() {}

    private:
        Index _id;

        ComponentsList _componentList;
    };

    /// Entity index comparison.
    inline auto operator==(Entity const &entity, Entity const &other) { return entity.getId() == other.getId(); }

    inline auto operator!=(Entity const &entity, Entity const &other) { return entity.getId() != other.getId(); }

}
