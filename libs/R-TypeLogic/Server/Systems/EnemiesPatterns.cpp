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
#include "R-TypeLogic/Global/Components/LifeComponent.hpp"
#include "R-TypeLogic/Global/Components/PlayerComponent.hpp"
#include "R-TypeLogic/Global/Components/PositionComponent.hpp"
#include "R-TypeLogic/Global/Components/VelocityComponent.hpp"
#include "R-TypeLogic/Global/SharedResources/Random.hpp"

#define MINIMUM_WIDTH  1200
#define MAXIMUM_WIDTH  1500
#define MINIMUM_HEIGTH 400
#define MAXIMUM_HEIGTH 900
#define SQUARE_SPACE   300

using namespace ecs;

/// @brief Make a enemy go random in defined limits
/// @param world the world where the random resource is
/// @param enemy the enemy who's going to randomly move
/// @param widthLimit the width limit for the randomness
/// @param heightLimit the height limit for the randomness
static void makeEnemyGoRandom(
    World &world, std::shared_ptr<Entity> enemy, std::pair<int, int> widthLimit, std::pair<int, int> heightLimit)
{
    Position &pos = enemy.get()->getComponent<Position>();
    Velocity &vel = enemy.get()->getComponent<Velocity>();
    Destination &dest = enemy.get()->getComponent<Destination>();

    if (pos.x >= dest.x - 10 && pos.x <= dest.x + 10 && pos.y >= dest.y - 10 && pos.y <= dest.y + 10) {
        double newVelX = 0;
        double newVelY = 0;
        RandomDevice &random = world.getResource<RandomDevice>();
        random.lock();
        dest.x = random.randInt(widthLimit.first, widthLimit.second);
        dest.y = random.randInt(heightLimit.first, heightLimit.second);
        random.unlock();
        newVelX = dest.x - (int)pos.x;
        newVelY = dest.y - (int)pos.y;
        vel.multiplierAbscissa = newVelX;
        vel.multiplierOrdinate = newVelY;
        vel.modified = true;
        pos.modified = true;
    }
}

/// @brief Apply the basic pattern (random one) to the enemy
/// @param world the world where the random resource is
/// @param enemy the enemy who's going to randomly move
static void basicEnemyPatterns(World &world, std::shared_ptr<Entity> enemy)
{
    makeEnemyGoRandom(world, enemy, std::pair<int, int>(MINIMUM_WIDTH, MAXIMUM_WIDTH),
        std::pair<int, int>(MINIMUM_HEIGTH, MAXIMUM_HEIGTH));
}

/// @brief Apply the fire pattern (follow a player) to the enemy
/// @param world the world where the followed player is
/// @param enemy the enemy who's going to target the player
static void fireEnemyPatterns(World &world, std::shared_ptr<Entity> enemy)
{
    std::vector<std::shared_ptr<Entity>> players = world.joinEntities<Player>();
    auto guard = std::lock_guard(*enemy.get());
    Velocity &vel = enemy.get()->getComponent<Velocity>();
    Destination &dest = enemy.get()->getComponent<Destination>();

    if (players.empty()) {
        basicEnemyPatterns(world, enemy);
        return;
    }
    auto playerGuard = std::lock_guard(*players.at(0).get());
    Position &playerPos = players.at(0)->getComponent<Position>();
    Position &enemyPos = enemy->getComponent<Position>();

    if (playerPos.x - 100 <= dest.x && dest.x <= playerPos.x + 100)
        return;

    dest.x = playerPos.x;
    dest.y = playerPos.y;

    vel.multiplierAbscissa = (dest.x - enemyPos.x) / 10;
    vel.multiplierOrdinate = (dest.y - enemyPos.y) / 10;
    vel.modified = true;
    enemyPos.modified = true;
}

/// @brief Apply the electric Pattern (flash shape) to the enemy
/// @param world the world where the super fast enemy is
/// @param enemy the super fast enemy
static void electricEnemyPatterns(World &world, std::shared_ptr<Entity> enemy)
{
    makeEnemyGoRandom(world, enemy, std::pair<int, int>(100, 1800), std::pair<int, int>(100, 900));
}

/// @brief Init the Ice Pattern (hord squared shape pattern)
/// @param iceEnemies all the enemies with the ice type
/// @param world the world where the enemies are
static void initIcePatterns(std::vector<std::shared_ptr<ecs::Entity>> iceEnemies, World &world)
{
    RandomDevice &random = world.getResource<RandomDevice>();
    int baseSquareX = 0;
    int baseSquareY = 0;
    std::size_t nbEnemies = iceEnemies.size();

    auto setIceEnemyBaseParam = [](std::shared_ptr<ecs::Entity> iceEnemy, std::pair<int, int> destParams,
                                    std::pair<int, int> posParams) {
        auto guard = std::lock_guard(*iceEnemy.get());
        Position &pos = iceEnemy.get()->getComponent<Position>();
        Destination &dest = iceEnemy.get()->getComponent<Destination>();

        dest.x = destParams.first;
        dest.y = destParams.second;
        pos.x = posParams.first;
        pos.y = posParams.second;
        pos.modified = true;
    };

    for (std::size_t x = 0; x < nbEnemies; x += 4) {
        random.lock();
        baseSquareX = random.randInt(MINIMUM_WIDTH, MAXIMUM_WIDTH);
        baseSquareY = random.randInt(MINIMUM_HEIGTH, MAXIMUM_HEIGTH);
        random.unlock();
        setIceEnemyBaseParam(iceEnemies.at(x), std::pair<int, int>(baseSquareX, baseSquareY),
            std::pair<int, int>(baseSquareX + SQUARE_SPACE, baseSquareY));
        if (x + 1 < nbEnemies) {
            setIceEnemyBaseParam(iceEnemies.at(x + 1), std::pair<int, int>(baseSquareX + SQUARE_SPACE, baseSquareY),
                std::pair<int, int>(baseSquareX + SQUARE_SPACE, baseSquareY - SQUARE_SPACE));
        }
        if (x + 2 < nbEnemies) {
            setIceEnemyBaseParam(iceEnemies.at(x + 2),
                std::pair<int, int>(baseSquareX + SQUARE_SPACE, baseSquareY - SQUARE_SPACE),
                std::pair<int, int>(baseSquareX, baseSquareY - SQUARE_SPACE));
        }
        if (x + 3 < nbEnemies) {
            setIceEnemyBaseParam(iceEnemies.at(x + 3), std::pair<int, int>(baseSquareX, baseSquareY - SQUARE_SPACE),
                std::pair<int, int>(baseSquareX, baseSquareY));
        }
    }
}

/// @brief Apply the Ice Pattern (hord squared shape pattern)
/// @param allEnemies all the enemies in the world
/// @param world the world where the enemies are
static void iceEnemyPatterns(std::vector<std::shared_ptr<ecs::Entity>> allEnemies, World &world)
{
    std::vector<std::shared_ptr<ecs::Entity>> iceEnemies;

    for (auto &it : allEnemies) {
        unsigned short enemyType;
        {
            auto enemyGuard = std::lock_guard(*it.get());
            enemyType = it.get()->getComponent<Enemy>().enemyType;
        };
        if (enemyType == Enemy::ICE) {
            iceEnemies.emplace_back(it);
        }
    }

    for (auto &it : iceEnemies) {
        std::pair<int, int> pos;
        {
            auto iceGuard = std::lock_guard(*it.get());
            Position &tmp = it->getComponent<Position>();
            pos.first = tmp.x;
            pos.second = tmp.y;
        };
        if (pos.first == 0 && pos.second == 0) {
            initIcePatterns(iceEnemies, world);
            break;
        }
    }

    std::size_t nbEnemies = iceEnemies.size();

    auto applySquarePatterns = [](std::shared_ptr<Entity> currEnemy, std::shared_ptr<Entity> previousEnemy) {
        auto firstGuard = std::lock_guard(*currEnemy.get());
        Position &pos = currEnemy.get()->getComponent<Position>();
        Destination &dest = currEnemy.get()->getComponent<Destination>();
        Velocity &vel = currEnemy.get()->getComponent<Velocity>();

        if (pos.x - 5 <= dest.x && dest.x <= pos.x + 5 && pos.y - 5 <= dest.y && dest.y <= pos.y + 5) {
            auto secondGuard = std::lock_guard(*previousEnemy.get());
            Position &newDest = previousEnemy.get()->getComponent<Position>();

            dest.x = newDest.x;
            dest.y = newDest.y;
            vel.multiplierAbscissa = 0;
            vel.multiplierOrdinate = 0;
            vel.modified = true;
            pos.modified = true;
        } else if (vel.multiplierAbscissa == 0 && vel.multiplierOrdinate == 0) {
            vel.multiplierAbscissa = (dest.x - pos.x) / 10;
            vel.multiplierOrdinate = (dest.y - pos.y) / 10;
            vel.modified = true;
            pos.modified = true;
        }
    };

    for (std::size_t x = 0; x < nbEnemies; x += 4) {
        if (x + 3 < nbEnemies) {
            applySquarePatterns(iceEnemies.at(x), iceEnemies.at(x + 3));
            applySquarePatterns(iceEnemies.at(x + 3), iceEnemies.at(x + 2));
            applySquarePatterns(iceEnemies.at(x + 2), iceEnemies.at(x + 1));
            applySquarePatterns(iceEnemies.at(x + 1), iceEnemies.at(x));
            continue;
        }
        if (x + 2 < nbEnemies) {
            applySquarePatterns(iceEnemies.at(x), iceEnemies.at(x + 2));
            applySquarePatterns(iceEnemies.at(x + 2), iceEnemies.at(x + 1));
            applySquarePatterns(iceEnemies.at(x + 1), iceEnemies.at(x));
            continue;
        }
        if (x + 1 < nbEnemies) {
            applySquarePatterns(iceEnemies.at(x), iceEnemies.at(x + 1));
            applySquarePatterns(iceEnemies.at(x + 1), iceEnemies.at(x));
            continue;
        }
        {
            auto lastGuard = std::lock_guard(*iceEnemies.at(x).get());
            iceEnemies.at(x)->getComponent<Life>().lifePoint = 0;
        };
    }
}

/// @brief Apply the boss pattern
/// @param world the world where the boss
/// @param boss the boss of the level, following his pawns patterns
static void bossPattern(World &world, std::shared_ptr<Entity> boss)
{
    std::vector<std::shared_ptr<Entity>> enemies = world.joinEntities<Enemy>();

    int nbFire = 0;
    int nbElectrical = 0;

    for (auto &it : enemies) {
        unsigned short enemyType;
        {
            auto guard = std::lock_guard(*it.get());
            enemyType = it.get()->getComponent<Enemy>().enemyType;
        };
        if (enemyType == Enemy::FIRE) {
            ++nbFire;
        } else if (enemyType == Enemy::ELECTRIC) {
            ++nbElectrical;
        }
    }
    if (nbFire == nbElectrical) {
        basicEnemyPatterns(world, boss);
    } else if (nbFire > nbElectrical) {
        fireEnemyPatterns(world, boss);
    } else {
        electricEnemyPatterns(world, boss);
    }
}

/// @brief Check if the first velocity of the Enemy as been set
/// @param enemy the checked enemy
/// @return true if the velocity hasn't been set before, false otherwise
static bool firstVelocityNotSet(std::shared_ptr<Entity> enemy)
{
    auto guard = std::lock_guard(*enemy.get());

    Position &pos = enemy.get()->getComponent<Position>();
    Velocity &vel = enemy.get()->getComponent<Velocity>();
    Destination &dest = enemy.get()->getComponent<Destination>();

    if (vel.multiplierAbscissa == 0 && vel.multiplierOrdinate == 0) {
        vel.multiplierAbscissa = dest.x - (int)pos.x;
        vel.multiplierOrdinate = dest.y - (int)pos.y;
        vel.modified = true;
        return true;
    }
    return false;
}

void EnemiesPatterns::run(World &world)
{
    std::vector<std::shared_ptr<ecs::Entity>> joined = world.joinEntities<Enemy, Position, Velocity, Destination>();

    auto applyPatterns = [&world](std::shared_ptr<ecs::Entity> entityPtr) {
        unsigned short enemyType;
        {
            auto guard = std::lock_guard(*entityPtr.get());
            enemyType = entityPtr.get()->getComponent<Enemy>().enemyType;
        };
        if (enemyType == Enemy::ICE)
            return;

        if (firstVelocityNotSet(entityPtr))
            return;
        switch (enemyType) {
            case Enemy::FIRE: fireEnemyPatterns(world, entityPtr); break;
            case Enemy::ELECTRIC: electricEnemyPatterns(world, entityPtr); break;
            case Enemy::BOSS: bossPattern(world, entityPtr); break;
            default: basicEnemyPatterns(world, entityPtr); break;
        };
    };
    std::for_each(joined.begin(), joined.end(), applyPatterns);
    iceEnemyPatterns(joined, world);
}
