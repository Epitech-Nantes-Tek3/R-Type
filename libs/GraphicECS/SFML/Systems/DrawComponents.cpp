/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** DrawComponents
*/

#include "DrawComponents.hpp"
#include <algorithm>
#include <mutex>
#include "GraphicsRectangleComponent.hpp"
#include "GraphicsTextComponent.hpp"
#include "GraphicsTextureResource.hpp"
#include "TextureName.hpp"
#include "R-TypeLogic/Global/Components/AlliedProjectileComponent.hpp"
#include "R-TypeLogic/Global/Components/EnemyProjectileComponent.hpp"
#include "R-TypeLogic/Global/Components/LayerLvL.hpp"
#include "R-TypeLogic/Global/Components/PositionComponent.hpp"
#include "R-TypeLogic/Global/Components/SizeComponent.hpp"

using namespace graphicECS::SFML::Systems;
using namespace graphicECS::SFML::Resources;
using namespace graphicECS::SFML::Components;

bool DrawComponents::compareLayer(std::shared_ptr<Entity> e1, std::shared_ptr<Entity> e2)
{
    return (e1->getComponent<LayerLvL>().layer < e2->getComponent<LayerLvL>().layer);
}

void DrawComponents::_drawComponent(World &world, RenderWindowResource &windowResource, std::shared_ptr<ecs::Entity> &entityPtr)
{
    auto entityGuard = std::lock_guard(*entityPtr.get());

    if (entityPtr->contains<GraphicsRectangleComponent>()) {
        if (world.containsResource<GraphicsTextureResource>()) {
            GraphicsTextureResource &textureResource = world.getResource<GraphicsTextureResource>();
            auto guard = std::lock_guard(textureResource);
            entityPtr->getComponent<GraphicsRectangleComponent>().shape.setTexture(
                textureResource._texturesList[entityPtr->getComponent<TextureName>().textureName].get());
        } else {
            entityPtr->getComponent<GraphicsRectangleComponent>().shape.setFillColor(sf::Color::White);
        }
        windowResource.window.draw(entityPtr->getComponent<GraphicsRectangleComponent>().shape);
        return;
    }
    if (entityPtr->contains<GraphicsTextComponent>()) {
        windowResource.window.draw(entityPtr->getComponent<GraphicsTextComponent>().text);
        return;
    }
    auto layerType = entityPtr->getComponent<LayerLvL>();
    if (layerType.layer == LayerLvL::layer_e::OBSTACLE || layerType.layer == LayerLvL::layer_e::ENEMY
        || layerType.layer == LayerLvL::layer_e::PLAYER || layerType.layer == LayerLvL::layer_e::PROJECTILE
        || layerType.layer == LayerLvL::EXIT_BUTTON) {
        auto entityPos = entityPtr->getComponent<Position>();
        auto entitySize = entityPtr->getComponent<Size>();

        entityPtr->addComponent<GraphicsRectangleComponent>(entityPos.x, entityPos.y, entitySize.x, entitySize.y);
        if (layerType.layer == LayerLvL::layer_e::PLAYER)
            entityPtr->addComponent<TextureName>(GraphicsTextureResource::PLAYER_STATIC);
        if (layerType.layer == LayerLvL::layer_e::ENEMY)
            entityPtr->addComponent<TextureName>(GraphicsTextureResource::ENEMY_STATIC);
        if (layerType.layer == LayerLvL::layer_e::PROJECTILE) {
            if (entityPtr->contains<EnemyProjectile>()) {
                entityPtr->addComponent<TextureName>(GraphicsTextureResource::PROJECTILE_ENEMY);
            }
            if (entityPtr->contains<AlliedProjectile>()) {
                entityPtr->addComponent<TextureName>(GraphicsTextureResource::PROJECTILE_ALLY);
            }
        }
        if (layerType.layer == LayerLvL::EXIT_BUTTON)
            entityPtr->addComponent<TextureName>(GraphicsTextureResource::EXIT_BUTTON);
    }
}

void DrawComponents::_updateWindow(World &world, std::vector<std::shared_ptr<Entity>> &layers)
{
    RenderWindowResource &windowResource = world.getResource<RenderWindowResource>();
    auto guard = std::lock_guard(windowResource);

    if (windowResource.window.isOpen()) {
        windowResource.window.clear(sf::Color(0x151123));
        std::sort(layers.begin(), layers.end(), compareLayer);
        for (auto &it : layers) {
            _drawComponent(world, windowResource, it);
        }
        windowResource.window.display();
    }
}

void DrawComponents::run(World &world)
{
    std::vector<std::shared_ptr<Entity>> layers = world.joinEntities<LayerLvL>();

    if (layers.empty() || !world.containsResource<RenderWindowResource>())
        return;
    _updateWindow(world, layers);
}
