/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** SfRectangleFollowEntitySystem
*/

#include "SfRectangleFollowEntitySystem.hpp"

using namespace rtypelogic::global;
using namespace graphic::sfml;

void SfRectangleFollowEntitySystem::run(World &world)
{
    std::vector<std::shared_ptr<Entity>> entities = world.joinEntities<GraphicsRectangleComponent, Position>();

    auto rectangle = [](std::shared_ptr<Entity> entityPtr) {
        entityPtr.get()->getComponent<GraphicsRectangleComponent>().shape.setPosition(
            entityPtr.get()->getComponent<Position>().x, entityPtr.get()->getComponent<Position>().y);
    };
    std::for_each(entities.begin(), entities.end(), rectangle);
}
