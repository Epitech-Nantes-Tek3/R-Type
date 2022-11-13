/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** CollidableSystem
*/

#include "CollidableSystem.hpp"
#include <mutex>
#include "Transisthor/TransisthorECSLogic/Both/Components/Networkable.hpp"
#include "R-TypeLogic/Global/Components/AlliedProjectileComponent.hpp"
#include "R-TypeLogic/Global/Components/CollidableComponent.hpp"
#include "R-TypeLogic/Global/Components/DamageComponent.hpp"
#include "R-TypeLogic/Global/Components/DeathComponent.hpp"
#include "R-TypeLogic/Global/Components/EnemyComponent.hpp"
#include "R-TypeLogic/Global/Components/EnemyProjectileComponent.hpp"
#include "R-TypeLogic/Global/Components/ObstacleComponent.hpp"
#include "R-TypeLogic/Global/Components/PlayerComponent.hpp"

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

/// @brief Cross all the players and return the name of the projectile parent
/// @param world The game world
/// @param networkId Networkable id of the parent
/// @return The parent name
static std::string getParentNameFromProjectile(World &world, unsigned short networkId)
{
    auto playerList = world.joinEntities<Player, Networkable>();

    for (auto it : playerList) {
        if (it->getComponent<Networkable>().id == networkId)
            return it->getComponent<Player>().name;
    }
    return "";
}

void Collide::enemiesKilledCounterByPlayer(
    World &world, std::shared_ptr<ecs::Entity> fstEntity, std::shared_ptr<ecs::Entity> sndEntity, Life &sndLife)
{
    if (sndLife.lifePoint == 0 && fstEntity->contains<Player>() && sndEntity->contains<Enemy>()) {
        auto apiAnswer = world.getTransisthorBridge()->getCommunicatorInstance().getDatabaseApi().selectUsers(
            "UserName = '" + fstEntity->getComponent<Player>().name + "'");
        if (apiAnswer.size() == 0)
            return;
        world.getTransisthorBridge()->getCommunicatorInstance().getDatabaseApi().updateUsers(
            "KilledEnemies = " + std::to_string(std::atoi(apiAnswer.at(0)["KilledEnemies"].c_str()) + 1),
            "UserName = '" + fstEntity->getComponent<Player>().name + "'");
    }
}

void Collide::enemiesKilledCounterByAlliedProjectile(
    World &world, std::shared_ptr<ecs::Entity> fstEntity, std::shared_ptr<ecs::Entity> sndEntity, Life &sndLife)
{
    if (sndLife.lifePoint == 0 && fstEntity->contains<AlliedProjectile>() && sndEntity->contains<Enemy>()) {
        auto apiAnswer = world.getTransisthorBridge()->getCommunicatorInstance().getDatabaseApi().selectUsers(
            "UserName = '"
            + getParentNameFromProjectile(world, fstEntity->getComponent<AlliedProjectile>().parentNetworkId) + "'");
        if (apiAnswer.size() == 0)
            return;
        world.getTransisthorBridge()->getCommunicatorInstance().getDatabaseApi().updateUsers(
            "KilledEnemies = " + std::to_string(std::atoi(apiAnswer.at(0)["KilledEnemies"].c_str()) + 1),
            "UserName = '"
                + getParentNameFromProjectile(world, fstEntity->getComponent<AlliedProjectile>().parentNetworkId)
                + "'");
    }
}

void Collide::collide(World &world, std::vector<std::shared_ptr<ecs::Entity>> &fstEntities,
    std::vector<std::shared_ptr<ecs::Entity>> &sndEntities)
{
    for (std::shared_ptr<ecs::Entity> fstEntity : fstEntities) {
        auto fstGuard = std::lock_guard(*fstEntity.get());
        Position &fstPos = fstEntity->getComponent<Position>();
        Size &fstSize = fstEntity->getComponent<Size>();

        if (fstEntity->contains<Death>())
            continue;
        for (std::shared_ptr<ecs::Entity> sndEntity : sndEntities) {
            auto sndGuard = std::lock_guard(*sndEntity.get());
            Position &sndPos = sndEntity->getComponent<Position>();
            Size &sndSize = sndEntity->getComponent<Size>();

            if (sndEntity->contains<Death>())
                continue;
            if (isSameHeight(fstPos, sndPos, fstSize, sndSize) && isSameWidth(fstPos, sndPos, fstSize, sndSize)) {
                Damage &fstDamage = fstEntity->getComponent<Damage>();
                Damage &sndDamage = sndEntity->getComponent<Damage>();

                if (fstEntity->contains<Life>() && fstEntity->getComponent<Life>().lifePoint > 0) {
                    Life &fstLife = fstEntity->getComponent<Life>();
                    if (sndDamage.damagePoint >= fstLife.lifePoint)
                        fstLife.lifePoint = sndDamage.damagePoint;
                    fstLife.lifePoint -= sndDamage.damagePoint;
                    fstLife.modified = true;
                }
                if (sndEntity->contains<Life>() && sndEntity->getComponent<Life>().lifePoint > 0) {
                    Life &sndLife = sndEntity->getComponent<Life>();
                    if (fstDamage.damagePoint >= sndLife.lifePoint)
                        sndLife.lifePoint = fstDamage.damagePoint;
                    sndLife.lifePoint -= fstDamage.damagePoint;
                    sndLife.modified = true;
                    enemiesKilledCounterByPlayer(world, fstEntity, sndEntity, sndLife);
                    enemiesKilledCounterByAlliedProjectile(world, fstEntity, sndEntity, sndLife);
                }
            }
        }
    }
}

void Collide::enemyCollide(World &world, std::vector<std::shared_ptr<ecs::Entity>> &enemiesProjectiles,
    std::vector<std::shared_ptr<ecs::Entity>> &obstacles)
{
    collide(world, enemiesProjectiles, obstacles);
}

void Collide::allyCollide(World &world, std::vector<std::shared_ptr<ecs::Entity>> &allyEntities,
    std::vector<std::shared_ptr<ecs::Entity>> &enemies, std::vector<std::shared_ptr<ecs::Entity>> &enemiesProjectiles,
    std::vector<std::shared_ptr<ecs::Entity>> &obstacles)
{
    collide(world, allyEntities, enemies);
    collide(world, allyEntities, enemiesProjectiles);
    collide(world, allyEntities, obstacles);
}

void Collide::run(World &world)
{
    std::vector<std::shared_ptr<ecs::Entity>> players =
        world.joinEntities<Position, Size, Collidable, Damage, Player>();
    std::vector<std::shared_ptr<ecs::Entity>> alliedProjectiles =
        world.joinEntities<Position, Size, Collidable, Damage, AlliedProjectile>();
    std::vector<std::shared_ptr<ecs::Entity>> enemies = world.joinEntities<Position, Size, Collidable, Damage, Enemy>();
    std::vector<std::shared_ptr<ecs::Entity>> enemiesProjectiles =
        world.joinEntities<Position, Size, Collidable, Damage, EnemyProjectile>();
    std::vector<std::shared_ptr<ecs::Entity>> obstacles =
        world.joinEntities<Position, Size, Collidable, Damage, Obstacle>();

    allyCollide(world, players, enemies, enemiesProjectiles, obstacles);
    allyCollide(world, alliedProjectiles, enemies, enemiesProjectiles, obstacles);
    enemyCollide(world, enemiesProjectiles, obstacles);
}
