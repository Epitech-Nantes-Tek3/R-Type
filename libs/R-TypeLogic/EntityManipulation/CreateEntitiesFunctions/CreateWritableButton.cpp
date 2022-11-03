/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** CreateWritableButton
*/

#include "CreateWritableButton.hpp"
#include <mutex>
#include "R-TypeLogic/Global/Components/ButtonComponent.hpp"
#include "R-TypeLogic/Global/Components/LayerLvL.hpp"
#include "R-TypeLogic/Global/Components/PositionComponent.hpp"
#include "R-TypeLogic/Global/Components/SizeComponent.hpp"
#include "GraphicECS/SFML/Components/AssociatedIdComponent.hpp"

namespace ecs
{
    std::size_t createNewWritableButton(World &world, const int posX, const int posY, const int sizeX, const int sizeY,
        ButtonActionMap::buttonAction_e actionName, MenuStates::menuState_e state, std::size_t associatedWritableId)
    {
        Entity &entity = world.addEntity();
        auto guard = std::lock_guard(entity);
        entity.addComponent<Button>()
            .addComponent<Size>(sizeX, sizeY)
            .addComponent<Position>(posX, posY)
            .addComponent<LayerLvL>(LayerLvL::WRITABLE_BUTTON)
            .addComponent<ActionName>(actionName)
            .addComponent<DisplayState>(state)
            .addComponent<graphicECS::SFML::Components::AssociatedId>(std::vector<std::size_t>(associatedWritableId));
        return entity.getId();
    }
} // namespace ecs
