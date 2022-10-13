/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** DrawComponents
*/

#include "DrawComponents.hpp"
#include "GraphicsRectangleComponent.hpp"
#include "GraphicsTextComponent.hpp"
#include "LayerLvL.hpp"
#include "SFMLResource/RenderWindowResource.hpp"
#include "World/World.hpp"

using namespace ecs;

void DrawComponents::run(World &world)
{
    std::vector<std::shared_ptr<Entity>> Inputs = world.joinEntities<LayerLvL>();

    world.getResource<RenderWindowResource>().window.clear();
    for (std::size_t layerI = 1; layerI < LayerLvL::LAYER_NUMBER; layerI++) {
        auto layer = [&layerI, &world](std::shared_ptr<Entity> entityPtr) {
            if (entityPtr->getComponent<LayerLvL>().layer == layerI) {
                if (entityPtr->contains<GraphicsRectangleComponent>())
                    world.getResource<RenderWindowResource>().window.draw(
                        entityPtr->getComponent<GraphicsRectangleComponent>().shape);
                if (entityPtr->contains<GraphicsTextComponent>())
                    world.getResource<RenderWindowResource>().window.draw(
                        entityPtr->getComponent<GraphicsTextComponent>().text);
            }
        };
        std::for_each(Inputs.begin(), Inputs.end(), layer);
    }
    world.getResource<RenderWindowResource>().window.display();
}
