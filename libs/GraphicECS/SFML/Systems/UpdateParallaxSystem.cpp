/*
** EPITECH PROJECT, 2022
** Project
** File description:
** UpdateParallaxSystem
*/

#include "UpdateParallaxSystem.hpp"
#include "GraphicECS/SFML/Resources/GraphicsTextureResource.hpp"
#include "R-TypeLogic/Global/SharedResources/GameLevel.hpp"

using namespace graphicECS::SFML::Systems;
using namespace graphicECS::SFML::Resources;


/// @brief This function loads new backgrounds, filepaths are given in the vector passed in params
/// @param world the world where the backgrounds will be changed
/// @param newPaths a vector with the 3 paths for the new backgrounds assets
static void changeBackgrounds(World &world, std::vector<std::string> newPaths)
{
    if (!world.containsResource<GraphicsTextureResource>() || newPaths.size() != 3)
        return;
    GraphicsTextureResource &textList = world.getResource<GraphicsTextureResource>();

    textList.lock();
    textList.removeTexture(GraphicsTextureResource::BACKGROUND_LAYER_3);
    textList.removeTexture(GraphicsTextureResource::BACKGROUND_LAYER_2);
    textList.removeTexture(GraphicsTextureResource::BACKGROUND_LAYER_1);
    textList.addTexture(
        GraphicsTextureResource::BACKGROUND_LAYER_3, newPaths.at(0), sf::Vector2f(0, 0), sf::Vector2f(1920, 1080));
    textList.addTexture(
        GraphicsTextureResource::BACKGROUND_LAYER_2, newPaths.at(1), sf::Vector2f(0, 0), sf::Vector2f(1920, 1080));
    textList.addTexture(
        GraphicsTextureResource::BACKGROUND_LAYER_1, newPaths.at(2), sf::Vector2f(0, 0), sf::Vector2f(1920, 1080));
    textList.unlock();
}

void UpdateParallax::run(World &world)
{
    if (!world.containsResource<GameLevel>())
        return;
    GameLevel &gameLvl = world.getResource<GameLevel>();

    gameLvl.lock();
    GameLevel::level_e currLvl = gameLvl.getCurrentLevel();
    bool hasLevelChanged = gameLvl.hasLevelChanged();
    gameLvl.unlock();

    if (!hasLevelChanged)
        return;
    std::vector<std::string> newBackgrounds;
    switch (currLvl) {
        case GameLevel::LEVEL_TWO:
            newBackgrounds.emplace_back("assets/Backgrounds/middle.png");
            newBackgrounds.emplace_back("assets/Backgrounds/middle.png");
            newBackgrounds.emplace_back("assets/Backgrounds/middle.png");
            break;
        case GameLevel::LEVEL_THREE:
            newBackgrounds.emplace_back("assets/Backgrounds/back.png");
            newBackgrounds.emplace_back("assets/Backgrounds/back.png");
            newBackgrounds.emplace_back("assets/Backgrounds/back.png");
            break;
        case GameLevel::LEVEL_FORTH:
            newBackgrounds.emplace_back("assets/Backgrounds/far.png");
            newBackgrounds.emplace_back("assets/Backgrounds/far.png");
            newBackgrounds.emplace_back("assets/Backgrounds/far.png");
            break;
        case GameLevel::LEVEL_INFINITE:
            newBackgrounds.emplace_back("assets/Backgrounds/back.png");
            newBackgrounds.emplace_back("assets/Backgrounds/far.png");
            newBackgrounds.emplace_back("assets/Backgrounds/middle.png");
            break;
        default: break;
    };
    changeBackgrounds(world, newBackgrounds);
    gameLvl.lock();
    gameLvl.levelHasChanged();
    gameLvl.unlock();
}