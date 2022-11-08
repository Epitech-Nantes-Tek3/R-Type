/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** AnimationSystem
*/

#include "AnimationSystem.hpp"
#include <mutex>
#include "AnimationComponent.hpp"
#include "AnimationFrequencyComponent.hpp"
#include "GraphicsRectangleComponent.hpp"
#include "GraphicsTextureResource.hpp"
#include "R-TypeLogic/Global/SharedResources/GameClock.hpp"

using namespace graphicECS::SFML::Systems;
using namespace graphicECS::SFML::Resources;
using namespace graphicECS::SFML::Components;

void AnimationSystem::_updateFrequency(World &world, std::shared_ptr<ecs::Entity> entity)
{
    GameClock &clock = world.getResource<GameClock>();
    auto guard = std::lock_guard(clock);

    entity->getComponent<AnimationFrequencyComponent>().frequency -=
        std::chrono::duration<double>(clock.getElapsedTime());
}

void AnimationSystem::_updateAnimation(World &world, std::shared_ptr<ecs::Entity> entity)
{
    using texturesNamesVector = std::vector<GraphicsTextureResource::textureName_e>;
    using texturesMap = std::unordered_map<GraphicsTextureResource::textureName_e, std::shared_ptr<sf::Texture>>;

    AnimationComponent &animation = entity->getComponent<AnimationComponent>();
    texturesNamesVector texturesNames = animation.textures;
    std::size_t &currentTexturePos = animation.currentTexturePos;
    AnimationFrequencyComponent &animationFrequency = entity->getComponent<AnimationFrequencyComponent>();
    GraphicsTextureResource &textureRessource = world.getResource<GraphicsTextureResource>();
    {
        auto guard = std::lock_guard(textureRessource);
        texturesMap textures = textureRessource._texturesList;

        currentTexturePos = (currentTexturePos < texturesNames.size() - 1) ? currentTexturePos + 1 : 0;
        if (entity->contains<GraphicsRectangleComponent>()) {
            entity->getComponent<GraphicsRectangleComponent>().shape.setTexture(
                textures.at(texturesNames[currentTexturePos]).get());
        }
    }
    animationFrequency.frequency = animationFrequency.baseFrequency;
}

void AnimationSystem::run(World &world)
{
    std::vector<std::shared_ptr<Entity>> shapes = world.joinEntities<AnimationComponent, AnimationFrequencyComponent>();

    if (shapes.empty() || !world.containsResource<GameClock>() || !world.containsResource<GraphicsTextureResource>())
        return;
    for (auto entity : shapes) {
        auto guard = std::lock_guard(*entity.get());
        _updateFrequency(world, entity);
        if (entity->getComponent<AnimationFrequencyComponent>().frequency < std::chrono::duration<double>(0)) {
            _updateAnimation(world, entity);
        }
    }
}
