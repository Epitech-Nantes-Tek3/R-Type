/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** MouvementSystem
*/

#include "MouvementSystem.hpp"

void run(World &world)
{
    std::vector<std::shared_ptr<ecs::Entity>> joined = world.joinEntities<Position, Velocity>();

    auto move = [](std::shared_ptr<ecs::Entity> entityPtr) {
        Position &pos = entityPtr.get()->getComponent<Position>();
        Velocity &vel = entityPtr.get()->getComponent<Velocity>();

        pos.x += vel.multiplierAbscissa;
        pos.y += vel.multiplierOrdinate;
    };
    std::for_each(joined.begin(), joined.end(), move);
}