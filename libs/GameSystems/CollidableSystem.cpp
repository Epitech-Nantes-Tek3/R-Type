/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** CollidableSystem
*/

#include "CollidableSystem.hpp"
#include "GameComponents/PlayerComponent.hpp"
#include "GameComponents/EnemyComponent.hpp"
#include "GameComponents/EnemyProjectileComponent.hpp"
#include "GameComponents/AlliedProjectileComponent.hpp"
#include "GameComponents/ObstacleComponent.hpp"
#include "GameComponents/CollidableComponent.hpp"
#include "GameComponents/DamageComponent.hpp"
#include "GameComponents/LifeComponent.hpp"

using namespace ecs;

bool Collide::isSameWidth(Position &fstPos, Position &sndPos, Size &fstSize, Size &sndSize)
{
    bool fstBelowSnd = fstPos.y <= sndPos.y && sndPos.y <= fstPos.y + fstSize.y;
    bool fstAboveSnd = fstPos.y <= sndPos.y + sndSize.y && sndPos.y + sndSize.y <= fstPos.y + fstSize.y;
    bool sndBelowFst = sndPos.y <= fstPos.y && fstPos.y <= sndPos.y + sndSize.y;
    bool snfAboveFst = sndPos.y <= fstPos.y + fstSize.y && fstPos.y + fstSize.y <= sndPos.y + sndSize.y;

    return fstBelowSnd || fstAboveSnd || sndBelowFst || snfAboveFst;
}

bool Collide::isSameHeight(Position &fstPos, Position &sndPos, Size &fstSize, Size &sndSize)
{
    bool fstToTheRightSnd = fstPos.x <= sndPos.x && sndPos.x <= fstPos.x + fstSize.x;
    bool fstToTheLeftSnd = fstPos.x <= sndPos.x + sndSize.x && sndPos.x + sndSize.x <= fstPos.x + fstSize.x;
    bool sndToTheRightFst = sndPos.x <= fstPos.x && fstPos.x <= sndPos.x + sndSize.x;
    bool sndToTheLeftFst = sndPos.x <= fstPos.x + fstSize.x && fstPos.x + fstSize.x <= sndPos.x + sndSize.x;

    return fstToTheRightSnd || fstToTheLeftSnd || sndToTheRightFst || sndToTheLeftFst;
}

void Collide::collide(
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


void Collide::enemyCollide(std::vector<std::shared_ptr<ecs::Entity>> &enemiesProjectiles,
            std::vector<std::shared_ptr<ecs::Entity>> &obstacles)
{
    collide(enemiesProjectiles, obstacles);
}

void Collide::allyCollide(std::vector<std::shared_ptr<ecs::Entity>> &allyEntities,
            std::vector<std::shared_ptr<ecs::Entity>> &enemies,
            std::vector<std::shared_ptr<ecs::Entity>> &enemiesProjectiles,
            std::vector<std::shared_ptr<ecs::Entity>> &obstacles)
{
    collide(allyEntities, enemies);
    collide(allyEntities, enemiesProjectiles);
    collide(allyEntities, obstacles);
}

void Collide::run(World &world)
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
