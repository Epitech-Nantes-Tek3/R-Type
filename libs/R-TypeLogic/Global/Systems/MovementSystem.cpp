/*
** EPITECH PROJECT, 2022
** Project
** File description:
** MouvementSystem
*/

#include "MovementSystem.hpp"
#include <mutex>
#include "R-TypeLogic/Global/Components/DestinationComponent.hpp"
#include "R-TypeLogic/Global/Components/EnemyComponent.hpp"
#include "R-TypeLogic/Global/Components/PlayerComponent.hpp"
#include "R-TypeLogic/Global/Components/PositionComponent.hpp"
#include "R-TypeLogic/Global/Components/VelocityComponent.hpp"
#include "R-TypeLogic/Global/SharedResources/GameClock.hpp"

using namespace ecs;

void Movement::run(World &world)
{
    std::vector<std::shared_ptr<ecs::Entity>> joined = world.joinEntities<Position, Velocity>();

    auto move = [&world](std::shared_ptr<ecs::Entity> entityPtr) {
        auto guardEntity = std::lock_guard(*entityPtr.get());
        GameClock &clock = world.getResource<GameClock>();
        auto guard = std::lock_guard(clock);
        double elapsedTimeInSeconds = clock.getElapsedTime();
        Position &pos = entityPtr.get()->getComponent<Position>();
        Velocity &vel = entityPtr.get()->getComponent<Velocity>();

        if (vel.multiplierAbscissa == 0 && vel.multiplierOrdinate == 0)
            return;
        if (entityPtr->contains<Player>() == true) {
            if ((pos.x <= 4 && vel.multiplierAbscissa < 0))
                return;
            if ((pos.x >= 1912 && vel.multiplierAbscissa > 0))
                return;
            if ((pos.y <= 4 && vel.multiplierOrdinate < 0))
                return;
            if ((pos.y >= 1072 && vel.multiplierOrdinate > 0))
                return;
        }
        if (elapsedTimeInSeconds >= 1)
            return;
        pos.x += (vel.multiplierAbscissa * (((double((int)(elapsedTimeInSeconds * 100000000)))) / 100000000));
        pos.y += (vel.multiplierOrdinate * (((double((int)(elapsedTimeInSeconds * 100000000)))) / 100000000));
    };
    std::for_each(joined.begin(), joined.end(), move);
}
