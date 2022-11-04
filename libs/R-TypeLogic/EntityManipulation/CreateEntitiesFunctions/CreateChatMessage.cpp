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
#include "GraphicECS/SFML/Components/ChatMessageComponent.hpp"
#include "GraphicECS/SFML/Components/ChatMessageLifeComponent.hpp"

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
            .addComponent<graphicECS::SFML::Components::ChatMessage>(author, content)
            .addComponent<graphicECS::SFML::Components::ChatMessageLife>(frequency);
        return entity.getId();
    }
} // namespace ecs
