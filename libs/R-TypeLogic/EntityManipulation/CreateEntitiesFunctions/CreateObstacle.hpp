/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** CreateObstacle
*/

#ifndef CREATEOBSTACLE_HPP_
#define CREATEOBSTACLE_HPP_

#include "Transisthor/TransisthorECSLogic/Both/Components/Networkable.hpp"
#include "World/World.hpp"
#include "R-TypeLogic/Global/Components/CollidableComponent.hpp"
#include "R-TypeLogic/Global/Components/DamageComponent.hpp"
#include "R-TypeLogic/Global/Components/DamageRadiusComponent.hpp"
#include "R-TypeLogic/Global/Components/LayerLvL.hpp"
#include "R-TypeLogic/Global/Components/LifeComponent.hpp"
#include "R-TypeLogic/Global/Components/LifeTimeComponent.hpp"
#include "R-TypeLogic/Global/Components/NewlyCreated.hpp"
#include "R-TypeLogic/Global/Components/ObstacleComponent.hpp"
#include "R-TypeLogic/Global/Components/PositionComponent.hpp"
#include "R-TypeLogic/Global/Components/SizeComponent.hpp"
#include "R-TypeLogic/Global/Components/VelocityComponent.hpp"
#include "R-TypeLogic/Global/Components/WeightComponent.hpp"
#include "R-TypeLogic/Global/SharedResources/Random.hpp"

namespace ecs
{

    /// @brief This function can create a new Obstacle Entity in the world passed as params
    /// @param world The world in which the Obstacle must be created
    /// @param posX The position x of the new Obstacle
    /// @param posY The position y of the new Obstacle
    /// @param damage The damage inflicted to an Entity if this Entity hits this Obstacle
    /// @param uuid The uuid of the entity. Can be empty.
    /// @param networkId The id of the Networkable Component. In the client instance, it MUST NOT be filled in.
    /// @return Id of the new Obstacle in std::size_t
    std::size_t createNewObstacle(World &world, const int posX, const int posY, const unsigned short damage,
        const std::string uuid = "", unsigned short networkId = 0);
} // namespace ecs
#endif /* !CREATEOBSTACLE_HPP_ */
