/*
** EPITECH PROJECT, 2022
** Project
** File description:
** MobGenerationSystem
*/

#include "MobGenerationSystem.hpp"
#include "Transisthor/TransisthorECSLogic/Server/Resources/NetworkableIdGenerator.hpp"
#include "R-TypeLogic/EntityManipulation/CreateEntitiesFunctions/CreateEnemy.hpp"
#include "R-TypeLogic/Global/SharedResources/GameLevel.hpp"
#include "R-TypeLogic/Global/SharedResources/Random.hpp"

using namespace ecs;

/// @brief Generate infinite enemies
/// @param world the world where the enemies will be generated
/// @param hasLevelChanged if the level has changed, spawn a boss
/// Ice enemies cannot be generated here, so we randomise the type between
/// Enemy::BASIC = 0 and Enemy::ELECTRIC = 2
static void infiniteSpawn(World &world, bool hasLevelChanged)
{
    if (!world.containsResource<RandomDevice>())
        return;
    std::vector<std::shared_ptr<Entity>> joined = world.joinEntities<Enemy>();
    RandomDevice &random = world.getResource<RandomDevice>();
    std::size_t currNbEnemies = joined.size();

    if (hasLevelChanged) {
        // spawn a boss
    }

    random.lock();
    unsigned int newNbrsEnemies = random.randInt(10, 15);
    random.unlock();

    while (newNbrsEnemies > currNbEnemies) {
        random.lock();
        unsigned int newType = random.randInt(0, 2);
        random.unlock();

        unsigned int networkId = 0;
        if (world.containsResource<NetworkableIdGenerator>()) {
            NetworkableIdGenerator &gen = world.getResource<NetworkableIdGenerator>();

            gen.lock();
            networkId = gen.generateNewNetworkableId();
            gen.unlock();
        }
        switch (newType) {
            case Enemy::FIRE: createFireEnemy(world, networkId); break;
            case Enemy::ELECTRIC: createElectricEnemy(world, networkId); break;
            default: createBasicEnemy(world, networkId); break;
        }
        newNbrsEnemies--;
    }
}

/// @brief Generate the necessary mob for the level one
/// @param world the world where the mob will be generated
static void createLevelOne(World &world)
{
    for (int x = 0; x < 5; x++) {
        unsigned int networkId = 0;

        if (world.containsResource<NetworkableIdGenerator>()) {
            NetworkableIdGenerator &gen = world.getResource<NetworkableIdGenerator>();

            gen.lock();
            networkId = gen.generateNewNetworkableId();
            gen.unlock();
        }
        createBasicEnemy(world, networkId);
    }
}

/// @brief Generate the necessary mob for the level two
/// @param world the world where the mob will be generated
static void createLevelTwo(World &world)
{
    for (int x = 0; x < 5; x++) {
        unsigned int networkId = 0;

        if (world.containsResource<NetworkableIdGenerator>()) {
            NetworkableIdGenerator &gen = world.getResource<NetworkableIdGenerator>();

            gen.lock();
            networkId = gen.generateNewNetworkableId();
            gen.unlock();
        }
        if (x < 2) {
            createBasicEnemy(world, networkId);
        } else {
            createFireEnemy(world, networkId);
        }
    }
}

/// @brief Generate the necessary mob for the level three
/// @param world the world where the mob will be generated
static void createLevelThree(World &world)
{
    for (int x = 0; x < 10; x++) {
        unsigned int networkId = 0;

        if (world.containsResource<NetworkableIdGenerator>()) {
            NetworkableIdGenerator &gen = world.getResource<NetworkableIdGenerator>();

            gen.lock();
            networkId = gen.generateNewNetworkableId();
            gen.unlock();
        }
        if (x < 2) {
            createBasicEnemy(world, networkId);
        } else {
            createIceEnemy(world, networkId);
        }
    }
}

void MobGeneration::run(World &world)
{
    if (!world.containsResource<GameLevel>())
        return;

    GameLevel &gamelvl = world.getResource<GameLevel>();
    gamelvl.lock();
    GameLevel::level_e currLvl = gamelvl.getCurrentLevel();
    bool hasLevelChanged = gamelvl.hasLevelChanged();
    gamelvl.unlock();

    if (!hasLevelChanged && currLvl != GameLevel::INFINITE)
        return;
    if (hasLevelChanged) {
        switch (currLvl) {
            case GameLevel::LEVEL_ONE: createLevelOne(world); break;
            case GameLevel::LEVEL_TWO: createLevelTwo(world); break;
            case GameLevel::LEVEL_THREE: createLevelThree(world); break;
            case GameLevel::LEVEL_FORTH: break;
            default: infiniteSpawn(world, hasLevelChanged); break;
        }
        gamelvl.lock();
        gamelvl.levelHasChanged();
        gamelvl.unlock();
    } else {
        infiniteSpawn(world, hasLevelChanged);
    }
}