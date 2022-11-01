/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** SfObjectFollowEntitySystem
*/

#include "SfObjectFollowEntitySystem.hpp"

using namespace graphicECS::SFML::Systems;
using namespace graphicECS::SFML::Components;

void SfObjectFollowEntitySystem::run(World &world)
{
    std::vector<std::shared_ptr<Entity>> entities = world.joinEntities<GraphicsRectangleComponent, Position>();
    std::vector<std::shared_ptr<Entity>> text = world.joinEntities<GraphicsTextComponent, Position, Velocity>();

    auto rectangle = [](std::shared_ptr<Entity> entityPtr) {
        auto guard = std::lock_guard(*entityPtr.get());
        entityPtr.get()->getComponent<GraphicsRectangleComponent>().shape.setPosition(
            entityPtr.get()->getComponent<Position>().x, entityPtr.get()->getComponent<Position>().y);
    };

    auto textMove = [](std::shared_ptr<Entity> entityPtr) {
        auto guard = std::lock_guard(*entityPtr.get());
        entityPtr.get()->getComponent<GraphicsTextComponent>().text.setPosition(
            entityPtr.get()->getComponent<Position>().x + entityPtr->getComponent<Size>().x * 0.5,
            entityPtr.get()->getComponent<Position>().y - entityPtr->getComponent<Size>().y * 0.1);
    };

    std::for_each(entities.begin(), entities.end(), rectangle);
    std::for_each(text.begin(), text.end(), textMove);
}
