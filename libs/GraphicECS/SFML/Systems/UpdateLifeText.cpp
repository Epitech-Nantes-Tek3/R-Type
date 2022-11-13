/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** UpdateLifeTextSystem
*/

#include "UpdateLifeText.hpp"
#include <mutex>
#include "GraphicsTextComponent.hpp"
#include "R-TypeLogic/Global/Components/ControlableComponent.hpp"
#include "R-TypeLogic/Global/Components/LifeComponent.hpp"
#include "R-TypeLogic/Global/Components/TextComponent.hpp"

using namespace graphicECS::SFML::Components;
using namespace graphicECS::SFML::Systems;

void UpdateLifeTextSystem::run(World &world)
{
    std::vector<std::shared_ptr<Entity>> text = world.joinEntities<TextComponent>();
    std::vector<std::shared_ptr<Entity>> player = world.joinEntities<Controlable>();

    if (text.empty() || player.empty())
        return;
    for (auto entity : text) {
        std::string &text = entity->getComponent<TextComponent>().text;
        std::size_t pos = text.find(": ");
        if (pos == std::string::npos)
            continue;
        pos += 2;
        if (std::atoi(text.c_str() + pos) == player.at(0)->getComponent<Life>().lifePoint)
            break;
        auto guard = std::lock_guard(*entity.get());
        text.replace(pos, text.size() - 1, std::to_string(player.at(0)->getComponent<Life>().lifePoint));
        if (entity->contains<GraphicsTextComponent>())
            entity->getComponent<GraphicsTextComponent>().text.setString(text);
    }
}
