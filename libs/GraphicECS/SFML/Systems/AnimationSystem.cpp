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

void AnimationSystem::run(World &world)
{
    std::vector<std::shared_ptr<Entity>> shapes =
        world.joinEntities<GraphicsRectangleComponent, AnimationComponent, AnimationFrequencyComponent>();

    if (shapes.empty())
        return;
    for (auto entity : shapes) {
        using texturesNamesVector = std::vector<GraphicsTextureResource::textureName_e>;
        using texturesMap = std::unordered_map<GraphicsTextureResource::textureName_e, std::shared_ptr<sf::Texture>>;
        auto entityGuard = std::lock_guard(*entity.get());
        {
            auto &clock = world.getResource<GameClock>();
            auto clockGuard = std::lock_guard(clock);
            entity->getComponent<AnimationFrequencyComponent>().frequency -=
                std::chrono::duration<double>(clock.getElapsedTime());
        }
        if (entity->getComponent<AnimationFrequencyComponent>().frequency < std::chrono::duration<double>(0)) {
            texturesNamesVector texturesNames = entity->getComponent<AnimationComponent>().textures;
            std::size_t &currentTexturePos = entity->getComponent<AnimationComponent>().currentTexturePos;
            {
                auto textureGuard = std::lock_guard(world.getResource<GraphicsTextureResource>());
                texturesMap textures = world.getResource<GraphicsTextureResource>()._texturesList;

                currentTexturePos = (currentTexturePos < texturesNames.size() - 1) ? currentTexturePos + 1 : 0;
                entity->getComponent<GraphicsRectangleComponent>().shape.setTexture(
                    textures.at(texturesNames[currentTexturePos]).get());
            }
            entity->getComponent<AnimationFrequencyComponent>().frequency =
                entity->getComponent<AnimationFrequencyComponent>().baseFrequency;
        }
    }
}
