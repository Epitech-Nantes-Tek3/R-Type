/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** CreateEnemyProjectile
*/

#ifndef CREATEENEMYPROJECTILE_HPP_
#define CREATEENEMYPROJECTILE_HPP_

#include "Transisthor/ECSLogic/Both/Components/Networkable.hpp"
#include "World/World.hpp"
#include "R-TypeLogic/Global/Components/CollidableComponent.hpp"
#include "R-TypeLogic/Global/Components/DamageComponent.hpp"
#include "R-TypeLogic/Global/Components/DamageRadiusComponent.hpp"
#include "R-TypeLogic/Global/Components/EnemyProjectileComponent.hpp"
#include "R-TypeLogic/Global/Components/LayerLvL.hpp"
#include "R-TypeLogic/Global/Components/LifeComponent.hpp"
#include "R-TypeLogic/Global/Components/LifeTimeComponent.hpp"
#include "R-TypeLogic/Global/Components/NewlyCreated.hpp"
#include "R-TypeLogic/Global/Components/PositionComponent.hpp"
#include "R-TypeLogic/Global/Components/SizeComponent.hpp"
#include "R-TypeLogic/Global/Components/VelocityComponent.hpp"
#include "R-TypeLogic/Global/Components/WeightComponent.hpp"
#include "R-TypeLogic/Global/SharedResources/Random.hpp"

using namespace transisthor::ecslogic;
using namespace rtypelogic::global;

namespace rtypelogic::entitymanipulation
{
    /// @brief This function create a new Entity projectile_enemy when an enemy shoot
    /// @param world The world in which the EnemyProjectile must be created
    /// @param enemy Enemy who fired
    /// @param uuid The uuid of the entity. Can be empty.
    /// @param networkId The id of the Networkable Component. In the client instance, it MUST NOT be filled in.
    /// @return Id in size_t of the new Entity
    inline std::size_t createNewEnemyProjectile(ecs::World &world, std::shared_ptr<ecs::Entity> enemy,
        const std::string uuid = "", unsigned short networkId = 0)
    {
        Position pos = enemy.get()->getComponent<Position>();
        Damage damage = enemy.get()->getComponent<Damage>();

        ecs::Entity &entity = world.addEntity()
                                  .addComponent<Position>(pos.x, pos.y + 20)
                                  .addComponent<Velocity>(-400, 0)
                                  .addComponent<Weight>(1)
                                  .addComponent<Size>(40, 40)
                                  .addComponent<LifeTime>(100)
                                  .addComponent<Life>(1)
                                  .addComponent<Damage>(damage)
                                  .addComponent<DamageRadius>(5)
                                  .addComponent<Collidable>()
                                  .addComponent<EnemyProjectile>(enemy.get()->getComponent<Networkable>().id);

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
            entity.addComponent<LayerLvL>(LayerLvL::layer_e::PROJECTILE);
        }
        return entity.getId();
    }
} // namespace rtypelogic::entitymanipulation
#endif /* !CREATEENEMYPROJECTILE_HPP_ */
