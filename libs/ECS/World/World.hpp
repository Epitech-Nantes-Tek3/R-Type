/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** World
*/

#pragma once

#include <map>
#include "Entity/Entity.hpp"
namespace ecs
{
    class World final {
      public:
        /// @brief The id type
        using Index = std::size_t;

        /// @brief This is the map of Entities in the World
        using EntitiesList = std::map<Index, std::unique_ptr<Entity>>;

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

        ~World() = default;

      protected:
      private:
        Index _id;
        EntitiesList _entitiesList;
        Index _nextEntityId;
    };
} // namespace ecs
