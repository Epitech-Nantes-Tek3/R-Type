/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** EnemiesPatterns
*/

#include "EnemiesPatterns.hpp"
#include <mutex>
#include "R-TypeLogic/Global/Components/DestinationComponent.hpp"
#include "R-TypeLogic/Global/Components/EnemyComponent.hpp"
#include "R-TypeLogic/Global/Components/PositionComponent.hpp"
#include "R-TypeLogic/Global/Components/VelocityComponent.hpp"
#include "R-TypeLogic/Global/SharedResources/Random.hpp"

#define MINIMUM_WIDTH  1400
#define MAXIMUM_WIDTH  1700
#define MINIMUM_HEIGTH 200
#define MAXIMUM_HEIGTH 800

using namespace ecs;

/// @brief Apply the basic pattern (random one) to the enemy
/// @param world the world where the random resource is
/// @param enemy the enemy who's going to randomly move
static void basicEnemyPatterns(World &world, std::shared_ptr<Entity> enemy)
{
    Position &pos = enemy.get()->getComponent<Position>();
    Velocity &vel = enemy.get()->getComponent<Velocity>();
    Destination &dest = enemy.get()->getComponent<Destination>();

    if (pos.x >= dest.x - 50 && pos.x <= dest.x + 50 && pos.y >= dest.y - 50 && pos.y <= dest.y + 50) {
        double newVelX = 0;
        double newVelY = 0;
        RandomDevice &random = world.getResource<RandomDevice>();
        auto guard = std::lock_guard(random);
        dest.x = random.randInt(MINIMUM_WIDTH, MAXIMUM_WIDTH);
        dest.y = random.randInt(MINIMUM_HEIGTH, MAXIMUM_HEIGTH);
        newVelX = dest.x - (int)pos.x;
        newVelY = dest.y - (int)pos.y;
        vel.multiplierAbscissa = (newVelX);
        vel.multiplierOrdinate = (newVelY);
        vel.modified = true;
        pos.modified = true;
    }
}

/// @brief Apply the fire pattern (follow a player) to the enemy
/// @param world the world where the followed player is
/// @param enemy the enemy who's going to target the player
static void fireEnemyPatterns(World &world, std::shared_ptr<Entity> enemy)
{
    (void)world;
    (void)enemy;
    /// Make him follow the player
}

/// @brief Apply the electric Pattern (flash shape) to the enemy
/// @param enemy the super fast enemy
static void electricEnemyPatterns(std::shared_ptr<Entity> enemy)
{
    (void)enemy;
    /// Make him go super fast, in a flash shape if possible
}

/// @brief  Apply the Ice Pattern (hord squared shape pattern) to the enemy
/// @param enemy the hord's member enemy
static void iceEnemyPatterns(std::shared_ptr<Entity> enemy)
{
    (void)enemy;
    /// Make him go in a squared shape, it will be a hord
}

/// @brief Check if the first velocity of the Enemy as been set
/// @param enemy the checked enemy
/// @return true if the velocity hasn't been set before, false otherwise
static bool firstVelocityNotSet(std::shared_ptr<Entity> enemy)
{
    Position &pos = enemy.get()->getComponent<Position>();
    Velocity &vel = enemy.get()->getComponent<Velocity>();
    Destination &dest = enemy.get()->getComponent<Destination>();

    if (vel.multiplierAbscissa == 0 && vel.multiplierOrdinate == 0) {
        vel.multiplierAbscissa = dest.x - (int)pos.x;
        vel.multiplierOrdinate = dest.y - (int)pos.y;
        vel.modified = true;
        pos.modified = true;
        return true;
    }
    return false;
}

void EnemiesPatterns::run(World &world)
{
    std::vector<std::shared_ptr<ecs::Entity>> joined = world.joinEntities<Enemy, Position, Velocity, Destination>();

    auto applyPatterns = [&world](std::shared_ptr<ecs::Entity> entityPtr) {
        auto guard = std::lock_guard(*entityPtr.get());

        if (firstVelocityNotSet(entityPtr))
            return;

        switch (entityPtr.get()->getComponent<Enemy>().enemyType) {
            case Enemy::FIRE: fireEnemyPatterns(world, entityPtr); break;
            case Enemy::ELECTRIC: electricEnemyPatterns(entityPtr); break;
            case Enemy::ICE: iceEnemyPatterns(entityPtr); break;
            default: basicEnemyPatterns(world, entityPtr); break;
        };
    };
    std::for_each(joined.begin(), joined.end(), applyPatterns);
}
