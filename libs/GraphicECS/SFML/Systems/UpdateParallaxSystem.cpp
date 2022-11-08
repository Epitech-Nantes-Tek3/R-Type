/*
** EPITECH PROJECT, 2022
** Project
** File description:
** UpdateParallaxSystem
*/

#include "UpdateParallaxSystem.hpp"
#include "R-TypeLogic/Global/SharedResources/GameLevel.hpp"

using namespace graphicsECS::SFML::Systems;

void UpdateParallax::run(World &world)
{
    if (!world.containsResource<GameLevel>())
        return;
    GameLevel &gameLvl = world.getResource<GameLevel>();

    gameLvl.lock();
    GameLevel::level_e currLvl = gameLvl.getCurrentLevel();
    gameLvl.unlock();

    switch (currLvl) {
        case GameLevel::LEVEL_TWO: break;
        case GameLevel::LEVEL_THREE: break;
        case GameLevel::LEVEL_FORTH: break;
        case GameLevel::LEVEL_INFINITE: break;
        default: break;
    };
}