/*
** EPITECH PROJECT, 2022
** Project
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
    RandomDevice &random = world.getResource<RandomDevice>();

    auto randomMove = [&random](std::shared_ptr<ecs::Entity> entityPtr) {
        Position &pos = entityPtr.get()->getComponent<Position>();
        Velocity &vel = entityPtr.get()->getComponent<Velocity>();
        Destination &dest = entityPtr.get()->getComponent<Destination>();

        if (pos.x == dest.x && pos.y == dest.y) {
            dest.x = random.randInt(MINIMUM_WIDTH, MAXIMUM_WIDTH);
            dest.y = random.randInt(MAXIMUM_WIDTH, MAXIMUM_HEIGTH);
        }
        vel.multiplierAbscissa = dest.x - pos.x;
        vel.multiplierOrdinate = dest.y - pos.y;
    };
    std::for_each(joined.begin(), joined.end(), randomMove);
}