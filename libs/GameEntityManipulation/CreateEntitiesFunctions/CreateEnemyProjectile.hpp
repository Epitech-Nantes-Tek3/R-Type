/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** CreateEnemyProjectile
*/

#ifndef CREATEENEMYPROJECTILE_HPP_
#define CREATEENEMYPROJECTILE_HPP_

#include "GameComponents/CollidableComponent.hpp"
#include "GameComponents/DamageComponent.hpp"
#include "GameComponents/DamageRadiusComponent.hpp"
#include "GameComponents/EnemyProjectileComponent.hpp"
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
    /// @brief This function create a new Entity projectile_enemy when an enemy shoot
    /// @param world The world in which the EnemyProjectile must be created
    /// @param enemy Enemy who fired
    /// @param uuid The uuid of the entity. Can be empty.
    /// @param networkId The id of the Networkable Component. In the client instance, it MUST NOT be filled in.
    /// @return Id in size_t of the new Entity
    std::size_t createNewEnemyProjectile(
        World &world, std::shared_ptr<ecs::Entity> enemy, const std::string uuid = "", unsigned short networkId = 0);
} // namespace ecs
#endif /* !CREATEENEMYPROJECTILE_HPP_ */
