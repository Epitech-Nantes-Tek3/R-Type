/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** SendNewlyCreatedToClients
*/

#include "Transisthor/ECSLogic/Server/Systems/SendNewlyCreatedToClients.hpp"
#include <chrono>
#include <thread>
#include "Transisthor/ECSLogic/Both/Components/Networkable.hpp"
#include "Transisthor/ECSLogic/Both/Resources/SendingFrequency.hpp"
#include "Transisthor/ECSLogic/Server/Components/NetworkClient.hpp"
#include "R-TypeLogic/Global/Components/AlliedProjectileComponent.hpp"
#include "R-TypeLogic/Global/Components/DamageComponent.hpp"
#include "R-TypeLogic/Global/Components/DamageRadiusComponent.hpp"
#include "R-TypeLogic/Global/Components/EnemyComponent.hpp"
#include "R-TypeLogic/Global/Components/EnemyProjectileComponent.hpp"
#include "R-TypeLogic/Global/Components/LifeComponent.hpp"
#include "R-TypeLogic/Global/Components/NewlyCreated.hpp"
#include "R-TypeLogic/Global/Components/ObstacleComponent.hpp"
#include "R-TypeLogic/Global/Components/PlayerComponent.hpp"
#include "R-TypeLogic/Global/Components/PositionComponent.hpp"
#include "R-TypeLogic/Global/Components/ProjectileComponent.hpp"
#include "R-TypeLogic/Global/Components/SizeComponent.hpp"
#include "R-TypeLogic/Global/Components/VelocityComponent.hpp"
#include "R-TypeLogic/Global/Components/WeightComponent.hpp"

using namespace transisthor::ecslogic;

void SendNewlyCreatedToClients::runSystem(ecs::World &world)
{
    std::vector<std::shared_ptr<ecs::Entity>> clients = world.joinEntities<NetworkClient>();
    std::vector<std::shared_ptr<ecs::Entity>> joinedNewlyCreated = world.joinEntities<NewlyCreated>();
    std::vector<unsigned short> clientIdList;

    auto addToClientList = [&clientIdList](std::shared_ptr<ecs::Entity> entityPtr) {
        clientIdList.emplace_back(entityPtr.get()->getComponent<NetworkClient>().id);
    };

    auto update = [this, &world, &clientIdList](std::shared_ptr<ecs::Entity> entityPtr) {
        NewlyCreated &newlyCreated = entityPtr->getComponent<NewlyCreated>();

        if (newlyCreated.isClientInstance || newlyCreated.sended == true)
            return;
        if (entityPtr->contains<ecs::AlliedProjectile>()) {
            std::cerr << entityPtr->getComponent<AlliedProjectile>().parentNetworkId << std::endl;
            world.getTransisthorBridge()->transitEcsDataToNetworkDataEntityAlliedProjectile(
                entityPtr->getComponent<Networkable>().id, entityPtr->getComponent<AlliedProjectile>().parentNetworkId,
                newlyCreated.uuid,
                {world.getEntity(entityPtr->getComponent<AlliedProjectile>().parentNetworkId)
                        .getComponent<NetworkClient>()
                        .id});
            std::vector<unsigned short> clientIdListWithoutParent;
            for (auto i : clientIdList) {
                if (i
                    != world.getEntity(entityPtr->getComponent<AlliedProjectile>().parentNetworkId)
                           .getComponent<NetworkClient>()
                           .id) {
                    clientIdListWithoutParent.emplace_back(i);
                }
            }
            if (!clientIdListWithoutParent.empty())
                world.getTransisthorBridge()->transitEcsDataToNetworkDataEntityAlliedProjectile(
                    entityPtr->getComponent<Networkable>().id,
                    entityPtr->getComponent<AlliedProjectile>().parentNetworkId, "", clientIdListWithoutParent);
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
        }
        if (entityPtr->contains<ecs::EnemyProjectile>()) {
            world.getTransisthorBridge()->transitEcsDataToNetworkDataEntityEnemyProjectile(
                entityPtr->getComponent<Networkable>().id, entityPtr->getComponent<EnemyProjectile>().parentNetworkId,
                newlyCreated.uuid, clientIdList);
        }
        if (entityPtr->contains<ecs::Obstacle>()) {
            Position &pos = entityPtr->getComponent<Position>();

            world.getTransisthorBridge()->transitEcsDataToNetworkDataEntityObstacle(
                entityPtr->getComponent<Networkable>().id, pos.x, pos.y, entityPtr->getComponent<Damage>().damagePoint,
                newlyCreated.uuid, clientIdList);
        }
        if (entityPtr->contains<ecs::Player>()) {
            Position &pos = entityPtr->getComponent<Position>();
            Velocity &vel = entityPtr->getComponent<Velocity>();
            Size &size = entityPtr->getComponent<Size>();

            world.getTransisthorBridge()->transitEcsDataToNetworkDataEntityPlayer(
                entityPtr->getComponent<Networkable>().id, pos.x, pos.y, vel.multiplierAbscissa, vel.multiplierOrdinate,
                entityPtr->getComponent<Weight>().weight, size.x, size.y, entityPtr->getComponent<Life>().lifePoint,
                entityPtr->getComponent<Damage>().damagePoint, entityPtr->getComponent<DamageRadius>().radius, false,
                newlyCreated.uuid, clientIdList);
        }
        if (entityPtr->contains<ecs::Projectile>()) {
            Position &pos = entityPtr->getComponent<Position>();
            Velocity &vel = entityPtr->getComponent<Velocity>();

            world.getTransisthorBridge()->transitEcsDataToNetworkDataEntityProjectile(
                entityPtr->getComponent<Networkable>().id, pos.x, pos.y, vel.multiplierAbscissa, vel.multiplierOrdinate,
                entityPtr->getComponent<Damage>().damagePoint, newlyCreated.uuid, clientIdList);
        }
        newlyCreated.sended = true;
        return;
    };

    std::for_each(clients.begin(), clients.end(), addToClientList);
    if (!clientIdList.empty())
        std::for_each(joinedNewlyCreated.begin(), joinedNewlyCreated.end(), update);
}
