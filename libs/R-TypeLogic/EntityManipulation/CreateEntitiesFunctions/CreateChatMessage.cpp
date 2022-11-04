/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** CreateChatMessage
*/

#include "CreateChatMessage.hpp"
#include <mutex>
#include "R-TypeLogic/Global/Components/LayerLvL.hpp"
#include "R-TypeLogic/Global/Components/PositionComponent.hpp"
#include "R-TypeLogic/Global/Components/SizeComponent.hpp"
#include "R-TypeLogic/EntityManipulation/ButtonManipulation/SharedResources/MenuStates.hpp"
#include "R-TypeLogic/EntityManipulation/ButtonManipulation/Components/DisplayState.hpp"

namespace ecs
{
    std::size_t createNewChatMessage(World &world, const int posX, const int posY, const int sizeX, const int sizeY,
        double frequency, std::string author, std::string content)
    {
        Entity &entity = world.addEntity();
        auto guard = std::lock_guard(entity);
        entity.addComponent<Size>(sizeX, sizeY)
            .addComponent<Position>(posX, posY)
            .addComponent<LayerLvL>(LayerLvL::CHAT_MESSAGE)
            .addComponent<DisplayState>(MenuStates::IN_GAME);
        (void)frequency;
        (void)author;
        (void)content;
        return entity.getId();
    }
} // namespace ecs
