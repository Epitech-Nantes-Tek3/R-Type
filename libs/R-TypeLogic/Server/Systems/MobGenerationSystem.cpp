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
/// Ice enemies cannot be generated here, so we randomise the type between
/// Enemy::BASIC = 0 and Enemy::ELECTRIC = 2
static void infiniteSpawn(World &world)
{
    if (!world.containsResource<RandomDevice>() || !world.containsResource<NetworkableIdGenerator>())
        return;
    RandomDevice &random = world.getResource<RandomDevice>();
    random.lock();
    unsigned int newType = random.randInt(0, 2);
    random.unlock();

    NetworkableIdGenerator &gen = world.getResource<NetworkableIdGenerator>();
    gen.lock();
    unsigned short id = gen.generateNewNetworkableId();
    gen.unlock();
    createNewEnemyRandom(world, 0, 0, 1, 34, 34, 40, 20, 5, newType, "", id);
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
            case GameLevel::LEVEL_ONE: return;
            case GameLevel::LEVEL_TWO: return;
            case GameLevel::LEVEL_THREE: return;
            case GameLevel::LEVEL_FORTH: return;
            default: break;
        }
    }
    infiniteSpawn(world);
}