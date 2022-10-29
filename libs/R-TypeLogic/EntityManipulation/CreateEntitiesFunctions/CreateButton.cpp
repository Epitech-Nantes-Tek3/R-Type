/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** CreateButton
*/

#include "CreateButton.hpp"
#include <mutex>
#include "R-TypeLogic/Global/Components/PositionComponent.hpp"
#include "R-TypeLogic/Global/Components/SizeComponent.hpp"

namespace ecs
{
    std::size_t createNewButton(World &world, const int posX, const int posY, const int sizeX, const int sizeY,
        ButtonActionMap::buttonAction_e actionName, LayerLvL::layer_e layerLvl, MenuStates::menuState_e state)
    {
        Entity &entity = world.addEntity();
        auto guard = std::lock_guard(entity);
        entity.addComponent<Button>()
            .addComponent<Size>(sizeX, sizeY)
            .addComponent<Position>(posX, posY)
            .addComponent<LayerLvL>(layerLvl)
            .addComponent<ActionName>(actionName)
            .addComponent<DisplayState>(state);
        return entity.getId();
    }
} // namespace ecs
