/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** CreateAlliedProjectile
*/

#ifndef CREATEALLYPROJECTILE_HPP_
#define CREATEALLYPROJECTILE_HPP_

#include "Transisthor/TransisthorECSLogic/Both/Components/Networkable.hpp"
#include "World/World.hpp"
#include "R-TypeLogic/Global/Components/AlliedProjectileComponent.hpp"
#include "R-TypeLogic/Global/Components/CollidableComponent.hpp"
#include "R-TypeLogic/Global/Components/DamageComponent.hpp"
#include "R-TypeLogic/Global/Components/DamageRadiusComponent.hpp"
#include "R-TypeLogic/Global/Components/LayerLvL.hpp"
#include "R-TypeLogic/Global/Components/LifeComponent.hpp"
#include "R-TypeLogic/Global/Components/LifeTimeComponent.hpp"
#include "R-TypeLogic/Global/Components/NewlyCreated.hpp"
#include "R-TypeLogic/Global/Components/PositionComponent.hpp"
#include "R-TypeLogic/Global/Components/SizeComponent.hpp"
#include "R-TypeLogic/Global/Components/VelocityComponent.hpp"
#include "R-TypeLogic/Global/Components/WeightComponent.hpp"
#include "R-TypeLogic/Global/Components/PlayerComponent.hpp"
#include "R-TypeLogic/Global/SharedResources/Random.hpp"

namespace ecs
{
    /// @brief This function creates a new Entity projectile_ally when an ally shoot
    /// @param world The world in which the Enemy must be created
    /// @param ally Entity who fired an ally projectile
    /// @param uuid The uuid of the entity. Can be empty.
    /// @param networkId The id of the Networkable Component. In the client instance, it MUST NOT be filled in.
    /// @return Id in size_t of the new Entity
    std::size_t createNewAlliedProjectile(
        World &world, Entity &ally, const std::string uuid = "", unsigned short networkId = 0);
} // namespace ecs
#endif /* !CREATEALLYPROJECTILE_HPP_ */
