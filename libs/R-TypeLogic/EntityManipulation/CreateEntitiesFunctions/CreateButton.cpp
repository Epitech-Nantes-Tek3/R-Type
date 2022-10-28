/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** CreateButton
*/

#include "CreateButton.hpp"
#include "R-TypeLogic/Global/Components/PositionComponent.hpp"
#include "R-TypeLogic/Global/Components/SizeComponent.hpp"

namespace ecs
{
    std::size_t createNewButton(World &world, const int posX, const int posY, const int sizeX, const int sizeY,
        ButtonActionMap::buttonAction_e actionName, LayerLvL::layer_e layerLvl)
    {
        return world.addEntity()
            .addComponent<Button>()
            .addComponent<Size>(sizeX, sizeY)
            .addComponent<Position>(posX, posY)
            .addComponent<LayerLvL>(layerLvl)
            .addComponent<ActionName>(actionName)
            .getId();
    }
} // namespace ecs