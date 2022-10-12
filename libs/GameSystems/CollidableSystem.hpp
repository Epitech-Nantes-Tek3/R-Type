/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** CollidableSystem
*/

#ifndef COLLIDABLESYSTEM_HPP_
#define COLLIDABLESYSTEM_HPP_

#include "World/World.hpp"
#include "GameComponents/PositionComponent.hpp"
#include "GameComponents/SizeComponent.hpp"

namespace ecs
{
    /// @brief This is the Collide System.
    /// This system will check every entities, see if they collide and apply damage on consequence
    /// Needed Component : Collidable, Position, Size, Damage
    struct Collide : public System {
        /// @brief isSameWidth Function
        /// This function checks if two entities have a common part on the map's width
        /// @param fstPos position of the first Entity
        /// @param sndPos position of the second Entity
        /// @param fstSize size of the first Entity
        /// @param sndSize size of the second Entity
        bool isSameWidth(Position &fstPos, Position &sndPos, Size &fstSize, Size &sndSize);

        /// @brief isSameHeight Function
        /// This function checks if two entities have a common part on the map's height
        /// @param fstPos position of the first Entity
        /// @param sndPos position of the second Entity
        /// @param fstSize size of the first Entity
        /// @param sndSize size of the second Entity
        bool isSameHeight(Position &fstPos, Position &sndPos, Size &fstSize, Size &sndSize);

        /// @brief Collide Function
        /// This function checks all the given entities passed in params, to see if they collide
        /// @param fstEntities first vector of entities to be checked
        /// @param sndEntities second vector of Entities to be checked
        void collide(
            std::vector<std::shared_ptr<ecs::Entity>> &fstEntities, std::vector<std::shared_ptr<ecs::Entity>> &sndEntities);

        /// @brief enemyCollide Function
        /// Check for enemy entities if they collide with obstacles
        /// @param enemiesProjectiles vector of entities containing the enemies' projectiles
        /// @param obstacles vector of entities containing the obstacles
        void enemyCollide(std::vector<std::shared_ptr<ecs::Entity>> &enemiesProjectiles,
            std::vector<std::shared_ptr<ecs::Entity>> &obstacles);

        /// @brief AllyCollide Function
        /// Check for every alliedEntities if they collide with enemyEntities
        /// @param allyEntities vector of entities which need to be checked if there is collision with the following params
        /// @param enemies vector of entities containing the enemies
        /// @param enemiesProjectiles vector of entities containing the enemies' projectiles
        /// @param obstacles vector of entities containing the obstacles
        void allyCollide(std::vector<std::shared_ptr<ecs::Entity>> &allyEntities,
            std::vector<std::shared_ptr<ecs::Entity>> &enemies,
            std::vector<std::shared_ptr<ecs::Entity>> &enemiesProjectiles,
            std::vector<std::shared_ptr<ecs::Entity>> &obstacles);

        void run(World &world) override final;
    };
} // namespace ecs

#endif /* !COLLIDABLESYSTEM_HPP_ */
