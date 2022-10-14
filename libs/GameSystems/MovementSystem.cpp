/*
** EPITECH PROJECT, 2022
** Project
** File description:
** MouvementSystem
*/

#include "MovementSystem.hpp"
#include "GameComponents/PositionComponent.hpp"
#include "GameComponents/VelocityComponent.hpp"
#include "GameSharedResources/GameClock.hpp"

using namespace ecs;

void Movement::run(World &world)
{
    std::vector<std::shared_ptr<ecs::Entity>> joined = world.joinEntities<Position, Velocity>();
    GameClock &clock = world.getResource<GameClock>();
    double elapsedTimeInSeconds = clock.getElapsedTime();

    auto move = [&elapsedTimeInSeconds](std::shared_ptr<ecs::Entity> entityPtr) {
        Position &pos = entityPtr.get()->getComponent<Position>();
        Velocity &vel = entityPtr.get()->getComponent<Velocity>();

        if (vel.multiplierAbscissa == 0 && vel.multiplierOrdinate == 0)
            return;
        pos.x += (vel.multiplierAbscissa * elapsedTimeInSeconds);
        pos.y += (vel.multiplierOrdinate * elapsedTimeInSeconds);
        pos.modified = true;
    };
    std::for_each(joined.begin(), joined.end(), move);
}
