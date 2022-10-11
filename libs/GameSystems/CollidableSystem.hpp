/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** CollidableSystem
*/

#ifndef COLLIDABLESYSTEM_HPP_
#define COLLIDABLESYSTEM_HPP_

#include "World/World.hpp"

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
        bool isSameWidth(Position &fstPos, Position &sndPos, Size &fstSize, Size &sndSize)
        {
            bool fstBelowSnd = fstPos.y <= sndPos.y && sndPos.y <= fstPos.y + fstSize.y;
            bool fstAboveSnd = fstPos.y <= sndPos.y + sndSize.y && sndPos.y + sndSize.y <= fstPos.y + fstSize.y;
            bool sndBelowFst = sndPos.y <= fstPos.y && fstPos.y <= sndPos.y + sndSize.y;
            bool snfAboveFst = sndPos.y <= fstPos.y + fstSize.y && fstPos.y + fstSize.y <= sndPos.y + sndSize.y;

            return fstBelowSnd || fstAboveSnd || sndBelowFst || snfAboveFst;
        }

        /// @brief isSameHeight Function
        /// This function checks if two entities have a common part on the map's height
        /// @param fstPos position of the first Entity
        /// @param sndPos position of the second Entity
        /// @param fstSize size of the first Entity
        /// @param sndSize size of the second Entity
        bool isSameHeight(Position &fstPos, Position &sndPos, Size &fstSize, Size &sndSize)
        {
            bool fstToTheRightSnd = fstPos.x <= sndPos.x && sndPos.x <= fstPos.x + fstSize.x;
            bool fstToTheLeftSnd = fstPos.x <= sndPos.x + sndSize.x && sndPos.x + sndSize.x <= fstPos.x + fstSize.x;
            bool sndToTheRightFst = sndPos.x <= fstPos.x && fstPos.x <= sndPos.x + sndSize.x;
            bool sndToTheLeftFst = sndPos.x <= fstPos.x + fstSize.x && fstPos.x + fstSize.x <= sndPos.x + sndSize.x;

            return fstToTheRightSnd || fstToTheLeftSnd || sndToTheRightFst || sndToTheLeftFst;
        }

        /// @brief Collide Function
        /// This function checks all the given entities given in params, to see if they collide
        /// @param fstEntities first vector of entities to be checked
        /// @param sndEntities second vector of Entities to be checked
        void collide(
            std::vector<std::shared_ptr<ecs::Entity>> &fstEntities, std::vector<std::shared_ptr<ecs::Entity>> &sndEntities)
        {
            for (std::shared_ptr<ecs::Entity> fstEntity : fstEntities) {
                Position &fstPos = fstEntity->getComponent<Position>();
                Size &fstSize = fstEntity->getComponent<Size>();

                for (std::shared_ptr<ecs::Entity> sndEntity : sndEntities) {
                    Position &sndPos = sndEntity->getComponent<Position>();
                    Size &sndSize = sndEntity->getComponent<Size>();

                    if (isSameHeight(fstPos, sndPos, fstSize, sndSize) && isSameWidth(fstPos, sndPos, fstSize, sndSize)) {
                        Damage &fstDamage = fstEntity->getComponent<Damage>();
                        Damage &sndDamage = sndEntity->getComponent<Damage>();

                        if (fstEntity->contains<Life>()) {
                            Life &fstLife = fstEntity->getComponent<Life>();
                            fstLife.lifePoint -= sndDamage.damagePoint;
                        }

                        if (sndEntity->contains<Life>()) {
                            Life &sndLife = sndEntity->getComponent<Life>();
                            sndLife.lifePoint -= fstDamage.damagePoint;
                        }
                    }
                }
            }
        }

        /// @brief enemyCollide Function
        /// Check for enemy entities if they collide with obstacles
        /// @param enemiesProjectiles vector of entities containing the enemies' projectiles
        /// @param obstacles vector of entities containing the obstacles
        void enemyCollide(std::vector<std::shared_ptr<ecs::Entity>> &enemiesProjectiles,
            std::vector<std::shared_ptr<ecs::Entity>> &obstacles)
        {
            collide(enemiesProjectiles, obstacles);
        }

        /// @brief AllyCollide Function
        /// Check for every alliedEntities if they collide with enemyEntities
        /// @param allyEntities vector of entities which need to be checked if there is collision with the following params
        /// @param enemies vector of entities containing the enemies
        /// @param enemiesProjectiles vector of entities containing the enemies' projectiles
        /// @param obstacles vector of entities containing the obstacles
        void allyCollide(std::vector<std::shared_ptr<ecs::Entity>> &allyEntities,
            std::vector<std::shared_ptr<ecs::Entity>> &enemies,
            std::vector<std::shared_ptr<ecs::Entity>> &enemiesProjectiles,
            std::vector<std::shared_ptr<ecs::Entity>> &obstacles)
        {
            collide(allyEntities, enemies);
            collide(allyEntities, enemiesProjectiles);
            collide(allyEntities, obstacles);
        }

        inline void run(World &world) override final
        {
            std::vector<std::shared_ptr<ecs::Entity>> players =
                world.joinEntities<Position, Size, Collidable, Damage, Player>();
            std::vector<std::shared_ptr<ecs::Entity>> alliedProjectiles =
                world.joinEntities<Position, Size, Collidable, Damage, AlliedProjectile>();
            std::vector<std::shared_ptr<ecs::Entity>> enemies =
                world.joinEntities<Position, Size, Collidable, Damage, Enemy>();
            std::vector<std::shared_ptr<ecs::Entity>> enemiesProjectiles =
                world.joinEntities<Position, Size, Collidable, Damage, EnemyProjectile>();
            std::vector<std::shared_ptr<ecs::Entity>> obstacles =
                world.joinEntities<Position, Size, Collidable, Damage, Obstacle>();

            allyCollide(players, enemies, enemiesProjectiles, obstacles);
            allyCollide(alliedProjectiles, enemies, enemiesProjectiles, obstacles);
            enemyCollide(enemiesProjectiles, obstacles);
        }
    };
} // namespace ecs

#endif /* !COLLIDABLESYSTEM_HPP_ */
