/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** DrawComponents
*/

#include "DrawComponents.hpp"
#include <algorithm>
#include "GameComponents/AlliedProjectileComponent.hpp"
#include "GameComponents/EnemyProjectileComponent.hpp"
#include "GameComponents/PositionComponent.hpp"
#include "GameComponents/SizeComponent.hpp"
#include "GraphicsRectangleComponent.hpp"
#include "GraphicsTextComponent.hpp"
#include "GraphicsTextureResource.hpp"
#include "LayerLvL.hpp"
#include "SFMLResource/RenderWindowResource.hpp"
#include "TextureName.hpp"

using namespace ecs;

bool DrawComponents::compareLayer(std::shared_ptr<Entity> e1, std::shared_ptr<Entity> e2)
{
    return (e1->getComponent<LayerLvL>().layer < e2->getComponent<LayerLvL>().layer);
}

void DrawComponents::drawBackgrounds(World &world, const std::vector<std::shared_ptr<Entity>> &Inputs)
{
    std::vector<std::size_t> bgIds;
    std::size_t middleId;
    std::size_t farId;
    std::size_t backId;

    for (std::shared_ptr<Entity> entityPtr : Inputs) {
        if (!entityPtr.get()->contains<TextureName>())
            continue;
        GraphicsTextureResource::textureName_e value = entityPtr->getComponent<TextureName>().textureName;
        switch (value) {
            case GraphicsTextureResource::BACKGROUND_LAYER_1: middleId = entityPtr.get()->getId(); break;
            case GraphicsTextureResource::BACKGROUND_LAYER_2: farId = entityPtr.get()->getId(); break;
            case GraphicsTextureResource::BACKGROUND_LAYER_3: backId = entityPtr.get()->getId(); break;
            default: break;
        }
    }
    bgIds.emplace_back(middleId);
    bgIds.emplace_back(farId);
    bgIds.emplace_back(backId);
    for (std::size_t background : bgIds) {
        Entity &bg = world.getEntity(background);

        bg.getComponent<GraphicsRectangleComponent>().shape.setTexture(
            world.getResource<GraphicsTextureResource>()
                ._texturesList[bg.getComponent<TextureName>().textureName]
                .get());
        world.getResource<RenderWindowResource>().window.draw(bg.getComponent<GraphicsRectangleComponent>().shape);
    }
}

void DrawComponents::run(World &world)
{
    std::vector<std::shared_ptr<Entity>> Inputs = world.joinEntities<LayerLvL>();

    if (world.getResource<RenderWindowResource>().window.isOpen()) {
        world.getResource<RenderWindowResource>().window.clear(sf::Color::Blue);
        std::sort(Inputs.begin(), Inputs.end(), compareLayer);
        //drawBackgrounds(world, Inputs);
        auto layer = [&world](std::shared_ptr<Entity> entityPtr) {
            if (entityPtr->contains<GraphicsRectangleComponent>()) {
                if (world.containsResource<GraphicsTextureResource>()) {
                    entityPtr->getComponent<GraphicsRectangleComponent>().shape.setTexture(
                        world.getResource<GraphicsTextureResource>()
                            ._texturesList[entityPtr->getComponent<TextureName>().textureName]
                            .get());
                } else {
                    entityPtr->getComponent<GraphicsRectangleComponent>().shape.setFillColor(sf::Color::White);
                }
                world.getResource<RenderWindowResource>().window.draw(
                    entityPtr->getComponent<GraphicsRectangleComponent>().shape);
                return;
            }
            if (entityPtr->contains<GraphicsTextComponent>()) {
                world.getResource<RenderWindowResource>().window.draw(
                    entityPtr->getComponent<GraphicsTextComponent>().text);
                return;
            }
            auto layerType = entityPtr->getComponent<LayerLvL>();
            if (layerType.layer == LayerLvL::layer_e::OBSTACLE || layerType.layer == LayerLvL::layer_e::ENEMY
                || layerType.layer == LayerLvL::layer_e::PLAYER || layerType.layer == LayerLvL::layer_e::PROJECTILE) {
                auto entityPos = entityPtr->getComponent<Position>();
                auto entitySize = entityPtr->getComponent<Size>();

                entityPtr->addComponent<GraphicsRectangleComponent>(
                    entityPos.x, entityPos.y, entitySize.x, entitySize.y);
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
            }
        };
        std::for_each(Inputs.begin(), Inputs.end(), layer);
        world.getResource<RenderWindowResource>().window.display();
    }
}
