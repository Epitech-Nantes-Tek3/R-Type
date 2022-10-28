/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** SfRectangleFollowEntitySystem
*/

#include "SfRectangleFollowEntitySystem.hpp"

void SfRectangleFollowEntitySystem::run(World &world)
{
    std::vector<std::shared_ptr<Entity>> entities = world.joinEntities<GraphicsRectangleComponent, Position>();

    auto rectangle = [](std::shared_ptr<Entity> entityPtr) {
        std::lock_guard(*entityPtr.get());
        entityPtr.get()->getComponent<GraphicsRectangleComponent>().shape.setPosition(
            entityPtr.get()->getComponent<Position>().x, entityPtr.get()->getComponent<Position>().y);
    };
    std::for_each(entities.begin(), entities.end(), rectangle);
}
