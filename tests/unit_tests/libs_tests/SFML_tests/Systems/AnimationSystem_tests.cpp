/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** AnimationSystem_tests
*/

#include <criterion/criterion.h>
#include "AnimationComponent.hpp"
#include "AnimationFrequencyComponent.hpp"
#include "AnimationSystem.hpp"
#include "GraphicECS/SFML/Components/GraphicsRectangleComponent.hpp"
#include "GraphicECS/SFML/Resources/GraphicsTextureResource.hpp"
#include "World/World.hpp"
#include "R-TypeLogic/Global/SharedResources/GameClock.hpp"

using namespace graphicECS::SFML::Components;
using namespace graphicECS::SFML::Systems;
using namespace graphicECS::SFML::Resources;

Test(AnimationSystem, create_basic_animation)
{
    World world(1);

    world.addEntity()
        .addComponent<AnimationComponent>()
        .addComponent<AnimationFrequencyComponent>()
        .addComponent<GraphicsRectangleComponent>();
    world.addResource<GameClock>();
    world.addResource<GraphicsTextureResource>(GraphicsTextureResource::PLAYER_STATIC_1,
        "assets/EpiSprite/BasicPlayerSpriteSheet.gif", sf::Vector2f(534 / 16 * 8, 0), sf::Vector2f(534 / 16, 34));
    world.getResource<GraphicsTextureResource>().addTexture(GraphicsTextureResource::PLAYER_STATIC_2,
        "assets/EpiSprite/BasicPlayerSpriteSheet.gif", sf::Vector2f(534 / 16 * 9, 0), sf::Vector2f(534 / 16, 34));
    world.getResource<GraphicsTextureResource>().addTexture(GraphicsTextureResource::PLAYER_STATIC_3,
        "assets/EpiSprite/BasicPlayerSpriteSheet.gif", sf::Vector2f(534 / 16 * 10, 0), sf::Vector2f(534 / 16, 34));
    world.getResource<GraphicsTextureResource>().addTexture(GraphicsTextureResource::PLAYER_STATIC_4,
        "assets/EpiSprite/BasicPlayerSpriteSheet.gif", sf::Vector2f(534 / 16 * 11, 0), sf::Vector2f(534 / 16, 34));
    world.getResource<GraphicsTextureResource>().addTexture(GraphicsTextureResource::PLAYER_STATIC_5,
        "assets/EpiSprite/BasicPlayerSpriteSheet.gif", sf::Vector2f(534 / 16 * 12, 0), sf::Vector2f(534 / 16, 34));
    world.getResource<GraphicsTextureResource>().addTexture(GraphicsTextureResource::PLAYER_STATIC_6,
        "assets/EpiSprite/BasicPlayerSpriteSheet.gif", sf::Vector2f(534 / 16 * 13, 0), sf::Vector2f(534 / 16, 34));
    world.getResource<GraphicsTextureResource>().addTexture(GraphicsTextureResource::PLAYER_STATIC_7,
        "assets/EpiSprite/BasicPlayerSpriteSheet.gif", sf::Vector2f(534 / 16 * 14, 0), sf::Vector2f(534 / 16, 34));
    world.getResource<GraphicsTextureResource>().addTexture(GraphicsTextureResource::PLAYER_STATIC_8,
        "assets/EpiSprite/BasicPlayerSpriteSheet.gif", sf::Vector2f(534 / 16 * 15, 0), sf::Vector2f(534 / 16, 34));
    auto animation = world.joinEntities<AnimationComponent>();
    for (auto &it : animation) {
        it->getComponent<AnimationComponent>().textures.push_back(GraphicsTextureResource::PLAYER_STATIC_1);
        it->getComponent<AnimationComponent>().textures.push_back(GraphicsTextureResource::PLAYER_STATIC_2);
        it->getComponent<AnimationComponent>().textures.push_back(GraphicsTextureResource::PLAYER_STATIC_3);
        it->getComponent<AnimationComponent>().textures.push_back(GraphicsTextureResource::PLAYER_STATIC_4);
        it->getComponent<AnimationComponent>().textures.push_back(GraphicsTextureResource::PLAYER_STATIC_5);
        it->getComponent<AnimationComponent>().textures.push_back(GraphicsTextureResource::PLAYER_STATIC_6);
        it->getComponent<AnimationComponent>().textures.push_back(GraphicsTextureResource::PLAYER_STATIC_7);
        it->getComponent<AnimationComponent>().textures.push_back(GraphicsTextureResource::PLAYER_STATIC_8);
    }
    world.addSystem<AnimationSystem>();
    world.runSystems();
    cr_assert_eq(1, 1);
}
