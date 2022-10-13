/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** DrawComponents
*/

#include "DrawComponents.hpp"
#include <algorithm>
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

void DrawComponents::run(World &world)
{
    std::vector<std::shared_ptr<Entity>> Inputs = world.joinEntities<LayerLvL>();

    world.getResource<RenderWindowResource>().window.clear();
    std::sort(Inputs.begin(), Inputs.end(), compareLayer);
    auto layer = [&world](std::shared_ptr<Entity> entityPtr) {
        if (entityPtr->contains<GraphicsRectangleComponent>())
            entityPtr->getComponent<GraphicsRectangleComponent>().shape.setTexture(
                world.getResource<GraphicsTextureResource>()
                    ._texturesList[entityPtr->getComponent<TextureName>().textureName]
                    .get());
        world.getResource<RenderWindowResource>().window.draw(
            entityPtr->getComponent<GraphicsRectangleComponent>().shape);
        if (entityPtr->contains<GraphicsTextComponent>())
            world.getResource<RenderWindowResource>().window.draw(
                entityPtr->getComponent<GraphicsTextComponent>().text);
    };
    std::for_each(Inputs.begin(), Inputs.end(), layer);
    world.getResource<RenderWindowResource>().window.display();
}
