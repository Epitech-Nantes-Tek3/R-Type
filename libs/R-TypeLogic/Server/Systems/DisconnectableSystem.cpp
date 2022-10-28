/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** DisconnectableSystem
*/

#include "DisconnectableSystem.hpp"
#include "Transisthor/TransisthorECSLogic/Server/Components/NetworkClient.hpp"
#include "R-TypeLogic/Global/Components/DeathComponent.hpp"
#include "R-TypeLogic/Global/Components/DisconnectableComponent.hpp"
#include <boost/asio/thread_pool.hpp>

using namespace ecs;

void DisconnectableSystem::run(World &world)
{
    std::vector<std::shared_ptr<ecs::Entity>> joined = world.joinEntities<Disconnectable>();

    auto disconnectableChange = [&world](std::shared_ptr<ecs::Entity> entityPtr) {
        std::lock_guard(*entityPtr.get());
        entityPtr->removeComponent<Disconnectable>();
        entityPtr->addComponent<Death>();
        entityPtr->getComponent<Death>().clientToDelete = entityPtr->getComponent<NetworkClient>().id;
        /// NB : WHEN A NEW RELATIVE OBJECT IS LINK TO A PLAYER, DONT FORGET TO ADD DEATH COMPONENT TO IT RIGHT
        /// THERE
    };

    std::for_each(joined.begin(), joined.end(), disconnectableChange);
}
