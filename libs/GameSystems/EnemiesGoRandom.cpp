/*
** EPITECH PROJECT, 2022
** Project
** File description:
** EnemiesGoRandom
*/

#include "EnemiesGoRandom.hpp"
#include "GameComponents/EnemyComponent.hpp"
#include "GameComponents/PositionComponent.hpp"
#include "GameComponents/VelocityComponent.hpp"
#include "GameComponents/DestinationComponent.hpp"
#include "GameSharedResources/Random.hpp"

using namespace ecs;

void EnemiesGoRandom::run(World &world)
{
    std::vector<std::shared_ptr<ecs::Entity>> joined = world.joinEntities<Enemy, Position, Velocity, Destination>();
    RandomDevice &random = world.getResource<RandomDevice>();

    auto randomMove = [](std::shared_ptr<ecs::Entity> entityPtr) {
        
    };
    std::for_each(joined.begin(), joined.end(), randomMove);
}