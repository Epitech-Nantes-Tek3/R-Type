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
    inline std::size_t createNewEnemyProjectile(
        World &world, Entity &enemy, const std::string uuid = "", unsigned short networkId = 0)
    {
        Position pos = enemy.getComponent<Position>();
        Damage damage = enemy.getComponent<Damage>();
        Velocity velocity = enemy.getComponent<Velocity>();

        Entity &entity = world.addEntity()
                             .addComponent<Position>(pos.x, pos.y)
                             .addComponent<Velocity>(velocity.multiplierAbscissa, velocity.multiplierOrdinate)
                             .addComponent<Weight>(1)
                             .addComponent<Size>(2, 1)
                             .addComponent<LifeTime>(100)
                             .addComponent<Life>(10)
                             .addComponent<Damage>(damage)
                             .addComponent<DamageRadius>(5)
                             .addComponent<Collidable>()
                             .addComponent<EnemyProjectile>(enemy.getComponent<Networkable>().id);

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
#endif /* !CREATEENEMYPROJECTILE_HPP_ */
