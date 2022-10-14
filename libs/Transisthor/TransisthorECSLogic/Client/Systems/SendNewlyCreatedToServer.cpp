/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** SendNewlyCreatedToServer
*/

#include "Transisthor/TransisthorECSLogic/Client/Systems/SendNewlyCreatedToServer.hpp"
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
#include "Transisthor/TransisthorECSLogic/Client/Components/NetworkServer.hpp"

using namespace ecs;

void SendNewlyCreatedToServer::runSystem(ecs::World &world)
{
    std::vector<std::shared_ptr<ecs::Entity>> servers = world.joinEntities<ecs::NetworkServer>();
    std::vector<std::shared_ptr<ecs::Entity>> joinedNewlyCreated = world.joinEntities<ecs::NewlyCreated>();
    std::vector<unsigned short> serverIdList;

    auto addToClientList = [&serverIdList](std::shared_ptr<ecs::Entity> entityPtr) {
        serverIdList.emplace_back(entityPtr.get()->getComponent<ecs::NetworkServer>().id);
    };

    auto update = [this, &world, &serverIdList](std::shared_ptr<ecs::Entity> entityPtr) {
        NewlyCreated &newlyCreated = entityPtr->getComponent<NewlyCreated>();

        if (!newlyCreated.isClientInstance)
            return;
        if (entityPtr->contains<ecs::AlliedProjectile>()) {
            std::cerr << newlyCreated.uuid << std::endl;
            world.getTransisthorBridge()->transitEcsDataToNetworkDataEntityAlliedProjectile(
                entityPtr->getComponent<Networkable>().id, entityPtr->getComponent<AlliedProjectile>().parentNetworkId, newlyCreated.uuid, serverIdList);
        }
        if (newlyCreated.uuid == "") {
            entityPtr->removeComponent<NewlyCreated>();
        }
        return;
    };

    std::for_each(servers.begin(), servers.end(), addToClientList);
    if (!serverIdList.empty())
        std::for_each(joinedNewlyCreated.begin(), joinedNewlyCreated.end(), update);
}
