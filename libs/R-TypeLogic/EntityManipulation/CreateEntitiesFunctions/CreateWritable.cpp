/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** CreateWritable
*/

#include "CreateWritable.hpp"
#include <mutex>
#include "R-TypeLogic/Global/Components/PositionComponent.hpp"
#include "R-TypeLogic/Global/Components/SizeComponent.hpp"
#include "R-TypeLogic/Global/Components/LayerLvL.hpp"
#include "R-TypeLogic/Global/Components/ButtonComponent.hpp"
#include "R-TypeLogic/EntityManipulation/ButtonManipulation/Components/ActionName.hpp"
#include "GraphicECS/SFML/Components/WritableContentComponent.hpp"

namespace ecs
{
    std::size_t createNewWritable(
        World &world, const int posX, const int posY, const int sizeX, const int sizeY, MenuStates::menuState_e state)
    {
        Entity &entity = world.addEntity();
        auto guard = std::lock_guard(entity);
        entity.addComponent<Button>()
            .addComponent<Size>(sizeX, sizeY)
            .addComponent<Position>(posX, posY)
            .addComponent<LayerLvL>(LayerLvL::WRITABLE)
            .addComponent<ActionName>(ButtonActionMap::PAUSE)
            .addComponent<DisplayState>(state)
            .addComponent<graphicECS::SFML::Components::WritableContent>();
        return entity.getId();
    }
} // namespace ecs
