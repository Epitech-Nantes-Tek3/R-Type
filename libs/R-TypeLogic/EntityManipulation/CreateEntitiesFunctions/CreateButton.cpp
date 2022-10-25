/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** CreateButton
*/

#include "CreateButton.hpp"
#include "R-TypeLogic/Global/Components/LayerLvL.hpp"

namespace ecs
{
    std::size_t createNewButton(World &world, const int posX, const int posY, const int sizeX, const int sizeY, GraphicsTextureResource::textureName_e textureName)
    {
        return world.addEntity()
            .addComponent<Button>()
            .addComponent<GraphicsRectangleComponent>(posX, posY, sizeX, sizeY)
            .addComponent<LayerLvL>(LayerLvL::layer_e::BUTTON)
            .addComponent<TextureName>(textureName)
            .getId();
    }
} // namespace ecs