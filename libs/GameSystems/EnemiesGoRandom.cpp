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
#define MAXIMUM_WIDTH  1920
#define MINIMUM_HEIGTH 0
#define MAXIMUM_HEIGTH 1080

using namespace ecs;

void EnemiesGoRandom::run(World &world)
{
    std::vector<std::shared_ptr<ecs::Entity>> joined = world.joinEntities<Enemy, Position, Velocity, Destination>();

    auto randomMove = [&world](std::shared_ptr<ecs::Entity> entityPtr) {
        Position &pos = entityPtr.get()->getComponent<Position>();
        Velocity &vel = entityPtr.get()->getComponent<Velocity>();
        Destination &dest = entityPtr.get()->getComponent<Destination>();

        if (vel.multiplierAbscissa == 0 && vel.multiplierOrdinate == 0) {
            vel.multiplierAbscissa = dest.x - pos.x;
            vel.multiplierOrdinate = dest.y - pos.y;
            return;
        }
        if (pos.x == dest.x || pos.y == dest.y) {
            int value = 0;
            int newVelX = 0;
            int newVelY = 0;

            dest.x = world.getResource<RandomDevice>().randInt(MINIMUM_WIDTH, MAXIMUM_WIDTH);
            dest.y = world.getResource<RandomDevice>().randInt(MINIMUM_HEIGTH, MAXIMUM_HEIGTH);
            newVelX = dest.x - pos.x;
            newVelY = dest.y - pos.y;
            do {
                /// That's some random values, just to make every enemy goes at a different speed
                value = world.getResource<RandomDevice>().randInt(1, 5);
            } while (newVelX % value != 0 && newVelY % value != 0);

            vel.multiplierAbscissa = (newVelX  / value);
            vel.multiplierOrdinate = (newVelY / value);
        }
    };
    std::for_each(joined.begin(), joined.end(), randomMove);
}