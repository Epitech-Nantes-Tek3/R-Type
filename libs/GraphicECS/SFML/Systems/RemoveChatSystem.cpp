/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** RemoveChatSystem
*/

#include "RemoveChatSystem.hpp"
#include <mutex>
#include "ChatMessageComponent.hpp"
#include "ChatMessageLifeComponent.hpp"
#include "R-TypeLogic/Global/SharedResources/GameClock.hpp"

using namespace graphicECS::SFML::Components;
using namespace graphicECS::SFML::Systems;

void RemoveChatSystem::_updateFrequency(World &world, std::shared_ptr<ecs::Entity> entity)
{
    GameClock &clock = world.getResource<GameClock>();
    auto guard = std::lock_guard(clock);

    entity->getComponent<ChatMessageLife>().frequency -= std::chrono::duration<double>(clock.getElapsedTime());
}

void RemoveChatSystem::run(World &world)
{
    std::vector<std::shared_ptr<Entity>> chatMessage = world.joinEntities<ChatMessage, ChatMessageLife>();

    if (chatMessage.empty() || !world.containsResource<GameClock>())
        return;
    for (auto entity : chatMessage) {
        auto guard = std::lock_guard(*entity.get());
        _updateFrequency(world, entity);
        if (entity->getComponent<ChatMessageLife>().frequency < std::chrono::duration<double>(0)) {
            world.removeEntity(entity->getId());
        }
    }
}
