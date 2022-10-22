/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** CreateAlliedProjectile
*/

#ifndef CREATEALLYPROJECTILE_HPP_
#define CREATEALLYPROJECTILE_HPP_

#include "GameComponents/AlliedProjectileComponent.hpp"
#include "GameComponents/CollidableComponent.hpp"
#include "GameComponents/DamageComponent.hpp"
#include "GameComponents/DamageRadiusComponent.hpp"
#include "GameComponents/LayerLvL.hpp"
#include "GameComponents/LifeComponent.hpp"
#include "GameComponents/LifeTimeComponent.hpp"
#include "GameComponents/NewlyCreated.hpp"
#include "GameComponents/PositionComponent.hpp"
#include "GameComponents/SizeComponent.hpp"
#include "GameComponents/VelocityComponent.hpp"
#include "GameComponents/WeightComponent.hpp"
#include "GameSharedResources/Random.hpp"
#include "Transisthor/TransisthorECSLogic/Both/Components/Networkable.hpp"
#include "World/World.hpp"

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
