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
    /// @param posX The position x of the new Obstacle
    /// @param posY The position y of the new Obstacle
    /// @param damage The damage inflicted to an Entity if this Entity hits this Obstacle
    /// @return Id of the new Obstacle in std::size_t
    inline std::size_t createNewObstacle(World &world, const int posX, const int posY, const unsigned short damage)
    {
        return world.addEntity()
            .addComponent<Position>(posX, posY)
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
