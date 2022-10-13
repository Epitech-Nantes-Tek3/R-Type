/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** DrawComponents
*/

#include "DrawComponents.hpp"
#include "World/World.hpp"
#include "RenderWindowResource.hpp"
#include "LayerLvL.hpp"
#include "GraphicsTextComponent.hpp"
#include "GraphicsRectangleComponent.hpp"

using namespace ecs;

void DrawComponents::run(World &world)
{
    std::vector<std::shared_ptr<Entity>> Inputs = world.joinEntities<LayerLvL>();

    std::for_each(Inputs.begin(), Inputs.end(), layer);
}