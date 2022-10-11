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
        bool isSameWidth(Position &fstPos, Position &sndPos, Size &fstSize, Size &sndSize)
        {
            bool fstBelowSnd = fstPos.y <= sndPos.y && sndPos.y <= fstPos.y + fstSize.y;
            bool fstAboveSnd = fstPos.y <= sndPos.y + sndSize.y && sndPos.y + sndSize.y <= fstPos.y + fstSize.y;
            bool sndBelowFst = sndPos.y <= fstPos.y && fstPos.y <= sndPos.y + sndSize.y;
            bool snfAboveFst = sndPos.y <= fstPos.y + fstSize.y && fstPos.y + fstSize.y <= sndPos.y + sndSize.y;

            return fstBelowSnd || fstAboveSnd || sndBelowFst || snfAboveFst;
        }

        bool isSameHeight(Position &fstPos, Position &sndPos, Size &fstSize, Size &sndSize)
        {
            bool fstToTheRightSnd = fstPos.x <= sndPos.x && sndPos.x <= fstPos.x + fstSize.x;
            bool fstToTheLeftSnd = fstPos.x <= sndPos.x + sndSize.x && sndPos.x + sndSize.x <= fstPos.x + fstSize.x;
            bool sndToTheRightFst = sndPos.x <= fstPos.x && fstPos.x <= sndPos.x + sndSize.x;
            bool sndToTheLeftFst = sndPos.x <= fstPos.x + fstSize.x && fstPos.x + fstSize.x <= sndPos.x + sndSize.x;

            return fstToTheRightSnd || fstToTheLeftSnd || sndToTheRightFst || sndToTheLeftFst;
        }

        void collide(
            std::vector<std::shared_ptr<ecs::Entity>> &first, std::vector<std::shared_ptr<ecs::Entity>> &second)
        {

        }

        void enemyCollide(gtd::vector<std::shared_ptr<ecs::Entity>> &enemyProjectiles,
            std::vector<std::shared_ptr<ecs::Entity>> &obstacles)
        {
            collide(enemyProjectiles, obstacles);
        }

        void allyCollide(std::vector<std::shared_ptr<ecs::Entity>> &allyEntities,
            std::vector<std::shared_ptr<ecs::Entity>> &enemies,
            std::vector<std::shared_ptr<ecs::Entity>> &enemyProjectiles,
            std::vector<std::shared_ptr<ecs::Entity>> &obstacles)
        {
            collide(allyEntities, enemies);
            collide(allyEntities, enemyProjectiles);
            collide(allyEntities, obstacles);
        }

        inline void run(World &world) override final
        {
            std::vector<std::shared_ptr<ecs::Entity>> players =
                world.joinEntities<Position, Size, Collidable, Damage, Player>();
            std::vector<std::shared_ptr<ecs::Entity>> alliedProjectiles =
                world.joinEntities<Position, Size, Collidable, Damage, alliedProjectiles>();
            std::vector<std::shared_ptr<ecs::Entity>> enemies =
                world.joinEntities<Position, Size, Collidable, Damage, Enemy>();
            std::vector<std::shared_ptr<ecs::Entity>> enemyProjectiles =
                world.joinEntities<Position, Size, Collidable, Damage, EnemyProjectile>();
            std::vector<std::shared_ptr<ecs::Entity>> obstacles =
                world.joinEntities<Position, Size, Collidable, Damage, Obstacle>();

            allyCollide(players, enemies, enemyProjectiles, obstacles);
            allyCollide(alliedProjectiles, enemies, enemyProjectiles, obstacles);
            enemyCollide(enemyProjectiles, obstacles);
        }
    };
} // namespace ecs

#endif /* !COLLIDABLESYSTEM_HPP_ */
