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
#include "R-TypeLogic/Global/Systems/UpdateClockSystem.hpp"

using namespace graphicECS::SFML::Components;
using namespace graphicECS::SFML::Systems;
using namespace graphicECS::SFML::Resources;

Test(AnimationSystem, create_basic_animation)
{
    World world(1);

    auto &entity = world.addEntity().addComponent<AnimationComponent>().addComponent<AnimationFrequencyComponent>();
    world.addResource<GameClock>();
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
    cr_assert_eq(entity.getComponent<AnimationComponent>().currentTexturePos, 0);
}

Test(AnimationSystem, use_basic_animation_and_wait_one_second)
{
    World world(1);

    auto &entity = world.addEntity().addComponent<AnimationComponent>().addComponent<AnimationFrequencyComponent>();
    world.addResource<GameClock>();
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
    world.addSystem<UpdateClock>();
    sleep(1);
    world.runSystems();
    cr_assert_eq(entity.getComponent<AnimationComponent>().currentTexturePos, 0);
}

Test(AnimationSystem, missing_resource)
{
    World world(1);

    auto &entity = world.addEntity().addComponent<AnimationComponent>().addComponent<AnimationFrequencyComponent>();
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
    cr_assert_eq(entity.getComponent<AnimationComponent>().currentTexturePos, 0);

}
