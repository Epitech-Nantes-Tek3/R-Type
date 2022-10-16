/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** EnemiesGoRandom
*/

#include "EnemiesGoRandom.hpp"
#include "GameComponents/DestinationComponent.hpp"
#include "GameComponents/EnemyComponent.hpp"
#include "GameComponents/PositionComponent.hpp"
#include "GameComponents/VelocityComponent.hpp"
#include "GameSharedResources/Random.hpp"

#define MINIMUM_WIDTH  1400
#define MAXIMUM_WIDTH  1700
#define MINIMUM_HEIGTH 0
#define MAXIMUM_HEIGTH 800

using namespace ecs;

void EnemiesGoRandom::run(World &world)
{
    std::vector<std::shared_ptr<ecs::Entity>> joined = world.joinEntities<Enemy, Position, Velocity, Destination>();

    auto randomMove = [&world](std::shared_ptr<ecs::Entity> entityPtr) {
        Position &pos = entityPtr.get()->getComponent<Position>();
        Velocity &vel = entityPtr.get()->getComponent<Velocity>();
        Destination &dest = entityPtr.get()->getComponent<Destination>();

        if (vel.multiplierAbscissa == 0 && vel.multiplierOrdinate == 0) {
            vel.multiplierAbscissa = dest.x - (int)pos.x;
            vel.multiplierOrdinate = dest.y - (int)pos.y;
            vel.modified = true;
            pos.modified = true;
            std::cerr << "Vel set : " << vel.multiplierAbscissa << " " << vel.multiplierOrdinate << std::endl;
            return;
        }
        if (pos.x >= dest.x - 50 && pos.x <= dest.x + 50 && pos.y >= dest.y - 50 && pos.y <= dest.y + 50) {
            double newVelX = 0;
            double newVelY = 0;

            dest.x = world.getResource<RandomDevice>().randInt(MINIMUM_WIDTH, MAXIMUM_WIDTH);
            dest.y = world.getResource<RandomDevice>().randInt(MINIMUM_HEIGTH, MAXIMUM_HEIGTH);
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