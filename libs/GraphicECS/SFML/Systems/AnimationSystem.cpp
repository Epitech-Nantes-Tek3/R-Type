/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** AnimationSystem
*/

#include <mutex>
#include "AnimationSystem.hpp"
#include "AnimationComponent.hpp"
#include "AnimationFrequencyComponent.hpp"
#include "GraphicsRectangleComponent.hpp"
#include "GraphicsTextureResource.hpp"
#include "R-TypeLogic/Global/SharedResources/GameClock.hpp"

using namespace graphicECS::SFML::Systems;
using namespace graphicECS::SFML::Resources;
using namespace graphicECS::SFML::Components;

void AnimationSystem::run(World &world)
{
    std::vector<std::shared_ptr<Entity>> shapes =
        world.joinEntities<GraphicsRectangleComponent, AnimationComponent, AnimationFrequencyComponent>();

    auto shape = [&world](std::shared_ptr<Entity> entity) {
        using texturesNamesVector = std::vector<GraphicsTextureResource::textureName_e>;
        using texturesMap = std::unordered_map<GraphicsTextureResource::textureName_e, std::shared_ptr<sf::Texture>>;
        std::lock_guard(*entity.get());
        entity->getComponent<AnimationFrequencyComponent>().frequency -= std::chrono::duration<double>(world.getResource<GameClock>().getElapsedTime());
        if (entity->getComponent<AnimationFrequencyComponent>().frequency < std::chrono::duration<double>(0)) {
            texturesNamesVector texturesNames = entity->getComponent<AnimationComponent>().textures;
            GraphicsTextureResource::textureName_e &currentTexture =
                entity->getComponent<AnimationComponent>().currentTexture;
            texturesMap textures = world.getResource<GraphicsTextureResource>()._texturesList;

            currentTexture = (currentTexture < textures.size())
                ? GraphicsTextureResource::textureName_e(currentTexture + 1)
                : GraphicsTextureResource::textureName_e(0);
            entity->getComponent<GraphicsRectangleComponent>().shape.setTexture(textures.at(currentTexture).get());
            entity->getComponent<AnimationFrequencyComponent>().frequency = entity->getComponent<AnimationFrequencyComponent>().baseFrequency;
        }
    };
    std::for_each(shapes.begin(), shapes.end(), shape);
}
