/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** SendNewlyCreatedToServer
*/

#include <boost/asio/thread_pool.hpp>
#include "Transisthor/TransisthorECSLogic/Client/Systems/SendNewlyCreatedToServer.hpp"
#include "Transisthor/TransisthorECSLogic/Both/Components/Networkable.hpp"
#include "Transisthor/TransisthorECSLogic/Client/Components/NetworkServer.hpp"
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

using namespace ecs;

void SendNewlyCreatedToServer::runSystem(ecs::World &world)
{
    std::vector<std::shared_ptr<ecs::Entity>> servers = world.joinEntities<ecs::NetworkServer>();
    std::vector<std::shared_ptr<ecs::Entity>> joinedNewlyCreated = world.joinEntities<ecs::NewlyCreated>();
    std::vector<unsigned short> serverIdList;

    auto addToClientList = [&serverIdList](std::shared_ptr<ecs::Entity> entityPtr) {
        std::lock_guard(*entityPtr.get());
        serverIdList.emplace_back(entityPtr.get()->getComponent<ecs::NetworkServer>().id);
    };

    auto update = [this, &world, &serverIdList](std::shared_ptr<ecs::Entity> entityPtr) {
        std::lock_guard(*entityPtr.get());
        NewlyCreated &newlyCreated = entityPtr->getComponent<NewlyCreated>();

        if (!newlyCreated.isClientInstance)
            return;
        if (newlyCreated.uuid == "") {
            entityPtr->removeComponent<NewlyCreated>();
            return;
        }
        if (entityPtr->contains<ecs::AlliedProjectile>() && newlyCreated.sended == false) {
            std::cerr << newlyCreated.uuid << std::endl;
            std::free(world.getTransisthorBridge()->transitEcsDataToNetworkDataEntityAlliedProjectile(
                entityPtr->getComponent<Networkable>().id, entityPtr->getComponent<AlliedProjectile>().parentNetworkId,
                newlyCreated.uuid, serverIdList));
            newlyCreated.sended = true;
        }
        return;
    };

    std::for_each(servers.begin(), servers.end(), addToClientList);
    if (!serverIdList.empty())
        std::for_each(joinedNewlyCreated.begin(), joinedNewlyCreated.end(), update);
}
