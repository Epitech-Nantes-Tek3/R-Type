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
#include "GameComponents/NewlyCreated.hpp"
#include "GameComponents/ObstacleComponent.hpp"
#include "GameComponents/PositionComponent.hpp"
#include "GameComponents/SizeComponent.hpp"
#include "GameComponents/VelocityComponent.hpp"
#include "GameComponents/WeightComponent.hpp"
#include "GameSharedResources/Random.hpp"
#include "Transisthor/TransisthorECSLogic/Both/Components/Networkable.hpp"
#include "World/World.hpp"

namespace ecs
{

    /// @brief This function can create a new Obstacle Entity in the world passed as params
    /// @param world The world in which the Obstacle must be created
    /// @param pos_x The position x of the new Obstacle
    /// @param pos_y The position y of the new Obstacle
    /// @param damage The damage inflicted to an Entity if this Entity hits this Obstacle
    /// @param uuid The uuid of the entity. Can be empty.
    /// @param networkId The id of the Networkable Component. In the client instance, it MUST NOT be filled in.
    /// @return Id of the new Obstacle in std::size_t
    inline std::size_t createNewObstacle(World &world, const int pos_x, const int pos_y, const unsigned short damage,
        const std::string uuid = "", unsigned short networkId = 0)
    {
        Entity &entity = world.addEntity()
                             .addComponent<Position>(pos_x, pos_y)
                             .addComponent<Weight>(1)
                             .addComponent<Size>(1, 1)
                             .addComponent<LifeTime>()
                             .addComponent<Life>(10)
                             .addComponent<Damage>(damage)
                             .addComponent<DamageRadius>(5)
                             .addComponent<Collidable>()
                             .addComponent<Obstacle>();

        if (networkId) {
            // Case : Creation in a server instance
            entity.addComponent<NewlyCreated>(uuid, false);
            entity.addComponent<Networkable>(networkId);
        } else {
            // Case : Creation in a Client instance
            if (uuid != "") {
                // Special case : the client created the entity and not the server
                entity.addComponent<NewlyCreated>(uuid, true);
            }
        }
        return entity.getId();
    }
} // namespace ecs
#endif /* !CREATEOBSTACLE_HPP_ */
