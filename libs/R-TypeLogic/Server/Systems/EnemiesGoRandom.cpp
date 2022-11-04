/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** EnemiesGoRandom
*/

#include "EnemiesGoRandom.hpp"
#include <mutex>
#include "R-TypeLogic/Global/Components/DestinationComponent.hpp"
#include "R-TypeLogic/Global/Components/EnemyComponent.hpp"
#include "R-TypeLogic/Global/Components/PositionComponent.hpp"
#include "R-TypeLogic/Global/Components/VelocityComponent.hpp"
#include "R-TypeLogic/Global/SharedResources/Random.hpp"
#include <iostream>

#define MINIMUM_WIDTH  1400
#define MAXIMUM_WIDTH  1700
#define MINIMUM_HEIGTH 200
#define MAXIMUM_HEIGTH 800

using namespace ecs;

void EnemiesGoRandom::run(World &world)
{
    std::vector<std::shared_ptr<ecs::Entity>> joined = world.joinEntities<Enemy, Position, Velocity, Destination>();

    std::cout << "test system go random";
    auto randomMove = [&world](std::shared_ptr<ecs::Entity> entityPtr) {
        auto guard = std::lock_guard(*entityPtr.get());
        Position &pos = entityPtr.get()->getComponent<Position>();
        Velocity &vel = entityPtr.get()->getComponent<Velocity>();
        Destination &dest = entityPtr.get()->getComponent<Destination>();

        if (vel.multiplierAbscissa == 0 && vel.multiplierOrdinate == 0) {
            vel.multiplierAbscissa = dest.x - (int)pos.x;
            vel.multiplierOrdinate = dest.y - (int)pos.y;
            vel.modified = true;
            pos.modified = true;
            return;
        }
        if (pos.x >= dest.x - 50 && pos.x <= dest.x + 50 && pos.y >= dest.y - 50 && pos.y <= dest.y + 50) {
            double newVelX = 0;
            double newVelY = 0;
            RandomDevice &random = world.getResource<RandomDevice>();
            auto guard = std::lock_guard(random);
            dest.x = random.randInt(MINIMUM_WIDTH, MAXIMUM_WIDTH);
            dest.y = random.randInt(MINIMUM_HEIGTH, MAXIMUM_HEIGTH);
            newVelX = dest.x - (int)pos.x;
            newVelY = dest.y - (int)pos.y;
            vel.multiplierAbscissa = (newVelX);
            vel.multiplierOrdinate = (newVelY);
            vel.modified = true;
            pos.modified = true;
        }
    };
    std::for_each(joined.begin(), joined.end(), randomMove);
}
