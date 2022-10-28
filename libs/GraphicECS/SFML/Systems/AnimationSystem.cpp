/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** AnimationSystem
*/

#include "AnimationSystem.hpp"
#include "GraphicsRectangleComponent.hpp"
// #include "AnimationDelayComponent.hpp"
#include "AnimationComponent.hpp"
#include "GraphicsTextureResource.hpp"

using namespace graphicECS::SFML::Systems;
using namespace graphicECS::SFML::Resources;
using namespace graphicECS::SFML::Components;

void AnimationSystem::run(World &world)
{
    std::vector<std::shared_ptr<Entity>> shapes = world.joinEntities<GraphicsRectangleComponent, AnimationComponent/*, AnimationDelayComponent*/>();

    auto shape = [&world](std::shared_ptr<Entity> entity) {
        using texturesNamesVector = std::vector<GraphicsTextureResource::textureName_e>;
        using texturesMap = std::unordered_map<GraphicsTextureResource::textureName_e, std::shared_ptr<sf::Texture>>;

        texturesNamesVector texturesNames = entity->getComponent<AnimationComponent>().textures;
        GraphicsTextureResource::textureName_e currentTexture = entity->getComponent<AnimationComponent>().currentTexture;
        texturesMap textures = world.getResource<GraphicsTextureResource>()._texturesList;

        entity->getComponent<GraphicsRectangleComponent>().shape.setTexture(textures.at(currentTexture).get());
    };
    std::for_each(shapes.begin(), shapes.end(), shape);
}
