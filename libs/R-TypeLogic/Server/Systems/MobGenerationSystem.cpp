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
#include "R-TypeLogic/Global/Components/PlayerComponent.hpp"

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
        GameLevel &gamelvl = world.getResource<GameLevel>();

        gamelvl.lock();
        gamelvl.levelHasChanged();
        gamelvl.unlock();

        unsigned int bossId = 0;
        if (world.containsResource<NetworkableIdGenerator>()) {
            NetworkableIdGenerator &gen = world.getResource<NetworkableIdGenerator>();

            gen.lock();
            bossId = gen.generateNewNetworkableId();
            gen.unlock();
        }
        createBoss(world, bossId);
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

/// @brief Generate the necessary mob for the level one (BASIC MOB)
/// @param world the world where the mob will be generated
static void createLevelOne(World &world, int nbplayers)
{
    for (int x = 0; x < (5 * nbplayers); x++) {
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

/// @brief Generate the necessary mob for the level two (FIRE MOB)
/// @param world the world where the mob will be generated
static void createLevelTwo(World &world, int nbplayers)
{
    for (int x = 0; x < (7 * nbplayers); x++) {
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

/// @brief Generate the necessary mob for the level three (ICE MOB)
/// @param world the world where the mob will be generated
static void createLevelThree(World &world, int nbplayers)
{
    for (int x = 0; x < (8 * nbplayers); x++) {
        unsigned int networkId = 0;

        if (world.containsResource<NetworkableIdGenerator>()) {
            NetworkableIdGenerator &gen = world.getResource<NetworkableIdGenerator>();

            gen.lock();
            networkId = gen.generateNewNetworkableId();
            gen.unlock();
        }
        createIceEnemy(world, networkId);
    }
}

/// @brief Generate the necessary mob for the forth level (ELECTRIC MOB)
/// @param world the world where the mob will be generated
static void createLevelFour(World &world, int nbplayers)
{
    for (int x = 0; x < (10 * nbplayers); x++) {
        unsigned int networkId = 0;

        if (world.containsResource<NetworkableIdGenerator>()) {
            NetworkableIdGenerator &gen = world.getResource<NetworkableIdGenerator>();

            gen.lock();
            networkId = gen.generateNewNetworkableId();
            gen.unlock();
        }
        createElectricEnemy(world, networkId);
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

    std::size_t nbPlayers = world.joinEntities<Player>().size();

    if (!hasLevelChanged && currLvl != GameLevel::LEVEL_INFINITE)
        return;
    if (hasLevelChanged) {
        switch (currLvl) {
            case GameLevel::LEVEL_ONE: createLevelOne(world, nbPlayers); break;
            case GameLevel::LEVEL_TWO: createLevelTwo(world, nbPlayers); break;
            case GameLevel::LEVEL_THREE: createLevelThree(world, nbPlayers); break;
            case GameLevel::LEVEL_FORTH: createLevelFour(world, nbPlayers); break;
            default: infiniteSpawn(world, hasLevelChanged); break;
        }
        gamelvl.lock();
        gamelvl.levelHasChanged();
        gamelvl.unlock();
    } else {
        infiniteSpawn(world, hasLevelChanged);
    }
}