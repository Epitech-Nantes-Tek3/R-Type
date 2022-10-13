/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** SendNewlyCreatedToClients
*/

#include "Transisthor/TransisthorECSLogic/Server/Systems/SendNewlyCreatedToClients.hpp"
#include "GameComponents/AlliedProjectileComponent.hpp"
#include "GameComponents/DamageComponent.hpp"
#include "GameComponents/DamageRadiusComponent.hpp"
#include "GameComponents/EnemyComponent.hpp"
#include "GameComponents/EnemyProjectileComponent.hpp"
#include "GameComponents/LifeComponent.hpp"
#include "GameComponents/NewlyCreated.hpp"
#include "GameComponents/ObstacleComponent.hpp"
#include "GameComponents/PlayerComponent.hpp"
#include "GameComponents/PositionComponent.hpp"
#include "GameComponents/ProjectileComponent.hpp"
#include "GameComponents/SizeComponent.hpp"
#include "GameComponents/VelocityComponent.hpp"
#include "GameComponents/WeightComponent.hpp"
#include "Transisthor/TransisthorECSLogic/Both/Components/Networkable.hpp"
#include "Transisthor/TransisthorECSLogic/Server/Components/NetworkClient.hpp"

using namespace ecs;

void SendNewlyCreatedToClients::runSystem(ecs::World &world)
{
    std::vector<std::shared_ptr<ecs::Entity>> clients = world.joinEntities<ecs::NetworkClient>();
    std::vector<std::shared_ptr<ecs::Entity>> joinedNewlyCreated = world.joinEntities<ecs::NewlyCreated>();
    std::vector<unsigned short> clientIdList;

    auto addToClientList = [&clientIdList](std::shared_ptr<ecs::Entity> entityPtr) {
        clientIdList.emplace_back(entityPtr.get()->getComponent<ecs::NetworkClient>().id);
    };

    auto update = [this, &world, &clientIdList](std::shared_ptr<ecs::Entity> entityPtr) {
        NewlyCreated &newlyCreated = entityPtr->getComponent<NewlyCreated>();

        if (newlyCreated.isClientInstance)
            return;
        if (entityPtr->contains<ecs::AlliedProjectile>()) {
            world.getTransisthorBridge()->transitEcsDataToNetworkDataEntityAlliedProjectile(
                entityPtr->getComponent<Networkable>().id, entityPtr->getId(), newlyCreated.uuid, clientIdList);
            return;
        }
        if (entityPtr->contains<ecs::Enemy>()) {
            Position &pos = entityPtr->getComponent<Position>();
            Velocity &vel = entityPtr->getComponent<Velocity>();
            Size &size = entityPtr->getComponent<Size>();

            world.getTransisthorBridge()->transitEcsDataToNetworkDataEntityEnemy(
                entityPtr->getComponent<Networkable>().id, pos.x, pos.y, vel.multiplierAbscissa, vel.multiplierOrdinate,
                entityPtr->getComponent<Weight>().weight, size.x, size.y, entityPtr->getComponent<Life>().lifePoint,
                entityPtr->getComponent<Damage>().damagePoint, entityPtr->getComponent<DamageRadius>().radius,
                newlyCreated.uuid, clientIdList);
            return;
        }
        if (entityPtr->contains<ecs::EnemyProjectile>()) {
            world.getTransisthorBridge()->transitEcsDataToNetworkDataEntityEnemyProjectile(
                entityPtr->getComponent<Networkable>().id, entityPtr->getId(), newlyCreated.uuid, clientIdList);
            return;
        }
        if (entityPtr->contains<ecs::Obstacle>()) {
            Position &pos = entityPtr->getComponent<Position>();

            world.getTransisthorBridge()->transitEcsDataToNetworkDataEntityObstacle(
                entityPtr->getComponent<Networkable>().id, pos.x, pos.y, entityPtr->getComponent<Damage>().damagePoint,
                newlyCreated.uuid, clientIdList);
            return;
        }
        if (entityPtr->contains<ecs::Player>()) {
            Position &pos = entityPtr->getComponent<Position>();
            Velocity &vel = entityPtr->getComponent<Velocity>();
            Size &size = entityPtr->getComponent<Size>();

            world.getTransisthorBridge()->transitEcsDataToNetworkDataEntityPlayer(
                entityPtr->getComponent<Networkable>().id, pos.x, pos.y, vel.multiplierAbscissa, vel.multiplierOrdinate,
                entityPtr->getComponent<Weight>().weight, size.x, size.y, entityPtr->getComponent<Life>().lifePoint,
                entityPtr->getComponent<Damage>().damagePoint, entityPtr->getComponent<DamageRadius>().radius,
                newlyCreated.uuid, clientIdList);
            return;
        }
        if (entityPtr->contains<ecs::Projectile>()) {
            Position &pos = entityPtr->getComponent<Position>();
            Velocity &vel = entityPtr->getComponent<Velocity>();

            world.getTransisthorBridge()->transitEcsDataToNetworkDataEntityProjectile(
                entityPtr->getComponent<Networkable>().id, pos.x, pos.y, vel.multiplierAbscissa, vel.multiplierOrdinate,
                entityPtr->getComponent<Damage>().damagePoint, newlyCreated.uuid, clientIdList);
            return;
        }
        if (newlyCreated.uuid == "") {
            entityPtr->removeComponent<NewlyCreated>();
        }
        return;
    };
    std::for_each(clients.begin(), clients.end(), addToClientList);
    if (!clientIdList.empty())
        std::for_each(joinedNewlyCreated.begin(), joinedNewlyCreated.end(), update);
}
