/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** CreateObstacle
*/

#ifndef CREATEOBSTACLE_HPP_
#define CREATEOBSTACLE_HPP_

#include <World/World.hpp>
#include <../GameComponents/PositionComponent.hpp>
#include <../GameComponents/VelocityComponent.hpp>
#include <../GameComponents/WeightComponent.hpp>
#include <../GameComponents/SizeComponent.hpp>
#include <../GameComponents/LifeTimeComponent.hpp>
#include <../GameComponents/DamageComponent.hpp>
#include <../GameComponents/LifeComponent.hpp>
#include <../GameComponents/DamageComponent.hpp>
#include <../GameComponents/DamageRadiusComponent.hpp>
#include <../GameComponents/CollidableComponent.hpp>
#include <../GameComponents/ObstacleComponent.hpp>
#include <../GameComponents/VelocityComponent.hpp>

using namespace ecs;

/// @brief This function can create a new Obstacle Entity in the world pass in params
/// @param world The world in that the Obstacle must be created
/// @param pos The position of the new Obstacle
/// @param damage The damage inflict at an Entity if this Entity hit this Obstacle
/// @return Id of the new Obstacle in std::size_t
inline std::size_t createNewObstacle(World &world, Position &pos, Damage &damage)
{
    std::size_t new_obstacle = world.addEntity()
                                    .addComponent<Position>(pos.x, pos.y)
                                    .addComponent<Weight>(1)
                                    .addComponent<Size>(1, 1)
                                    .addComponent<Lifetime>()
                                    .addComponent<Life>(10)
                                    .addComponent<Damage>(damage)
                                    .addComponent<DamageRadius>(5)
                                    .addComponent<Collidable>()
                                    .addComponent<Obstacle>()
                                    .getId();
    return new_obstacle;
}
#endif /* !CREATEOBSTACLE_HPP_ */
