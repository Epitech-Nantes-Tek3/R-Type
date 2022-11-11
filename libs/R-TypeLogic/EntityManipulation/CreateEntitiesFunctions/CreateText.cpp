/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** CreateText
*/

#include "CreateText.hpp"
#include <mutex>
#include "R-TypeLogic/Global/Components/PositionComponent.hpp"
#include "R-TypeLogic/Global/Components/SizeComponent.hpp"
#include "R-TypeLogic/Global/Components/TextComponent.hpp"

namespace ecs
{
    std::size_t createNewText(World &world, const int posX, const int posY, const int size, LayerLvL::layer_e layerLvl,
        MenuStates::menuState_e state, const std::string &text)
    {
        Entity &entity = world.addEntity();
        auto guard = std::lock_guard(entity);
        entity.addComponent<Position>(posX, posY)
            .addComponent<Size>(size, size)
            .addComponent<LayerLvL>(layerLvl)
            .addComponent<DisplayState>(state)
            .addComponent<TextComponent>(text);
        return entity.getId();
    }
} // namespace ecs
