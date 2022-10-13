/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** CreateObstacle
*/

#ifndef CREATEOBSTACLE_HPP_
#define CREATEOBSTACLE_HPP_

#include "GameComponents/CollidableComponent.hpp"
#include "GameComponents/DamageComponent.hpp"
#include "GameComponents/DamageRadiusComponent.hpp"
#include "GameComponents/LifeComponent.hpp"
#include "GameComponents/LifeTimeComponent.hpp"
#include "GameComponents/ObstacleComponent.hpp"
#include "GameComponents/PositionComponent.hpp"
#include "GameComponents/SizeComponent.hpp"
#include "GameComponents/VelocityComponent.hpp"
#include "GameComponents/WeightComponent.hpp"
#include "World/World.hpp"

namespace ecs
{

    /// @brief This function can create a new Obstacle Entity in the world passed as params
    /// @param world The world in which the Obstacle must be created
    /// @param pos_x The position x of the new Obstacle
    /// @param pos_y The position y of the new Obstacle
    /// @param damage The damage inflicted to an Entity if this Entity hits this Obstacle
    /// @return Id of the new Obstacle in std::size_t
    inline std::size_t createNewObstacle(World &world, const int pos_x, const int pos_y, const unsigned short damage)
    {
        return world.addEntity()
            .addComponent<Position>(pos_x, pos_y)
            .addComponent<Weight>(1)
            .addComponent<Size>(1, 1)
            .addComponent<LifeTime>()
            .addComponent<Life>(10)
            .addComponent<Damage>(damage)
            .addComponent<DamageRadius>(5)
            .addComponent<Collidable>()
            .addComponent<Obstacle>()
            .getId();
    }
} // namespace ecs
#endif /* !CREATEOBSTACLE_HPP_ */
