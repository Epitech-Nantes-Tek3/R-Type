/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** CreateAlliedProjectile
*/

#ifndef CREATEALLYPROJECTILE_HPP_
#define CREATEALLYPROJECTILE_HPP_

#include "World/World.hpp"
#include "GameComponents/CollidableComponent.hpp"
#include "GameComponents/DamageComponent.hpp"
#include "GameComponents/DamageRadiusComponent.hpp"
#include "GameComponents/LifeComponent.hpp"
#include "GameComponents/LifeTimeComponent.hpp"
#include "GameComponents/PositionComponent.hpp"
#include "GameComponents/AlliedProjectileComponent.hpp"
#include "GameComponents/SizeComponent.hpp"
#include "GameComponents/VelocityComponent.hpp"
#include "GameComponents/WeightComponent.hpp"

namespace ecs
{
    /// @brief This function creates a new Entity projectile_ally when an ally shoot
    /// @param world The world in that the Enemy must be created
    /// @param ally Entity who fired an ally projectile
    /// @return Id in size_t of the new Entity
    std::size_t createNewAlliedProjectile(World &world, Entity &ally);
} // namespace ecs
#endif /* !CREATEALLYPROJECTILE_HPP_ */
