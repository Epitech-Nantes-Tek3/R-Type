/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** SendToClient
*/

#include "SendToClient.hpp"
#include <mutex>
#include "Transisthor/TransisthorECSLogic/Both/Resources/SendingFrequency.hpp"

void SendToClient::runSystem(ecs::World &world)
{
    std::vector<std::shared_ptr<ecs::Entity>> clients = world.joinEntities<ecs::NetworkClient>();
    std::vector<std::shared_ptr<ecs::Entity>> joinedNetworkable = world.joinEntities<ecs::Networkable>();
    std::vector<unsigned short> clientIdList;

    auto addToClientList = [&clientIdList](std::shared_ptr<ecs::Entity> entityPtr) {
        auto guard = std::lock_guard(*entityPtr.get());
        clientIdList.emplace_back(entityPtr.get()->getComponent<ecs::NetworkClient>().id);
    };

    auto update = [this, &world, &clientIdList](std::shared_ptr<ecs::Entity> entityPtr) {
        auto guard = std::lock_guard(*entityPtr.get());
        unsigned short networkId = entityPtr->getComponent<ecs::Networkable>().id;
        sendToClients<ecs::Destination, ecs::Equipment, ecs::Invinsible, ecs::Invisible, ecs::Life, ecs::Position,
            ecs::Velocity, ecs::Death>(world, networkId, entityPtr, clientIdList);
        return;
    };

    std::for_each(clients.begin(), clients.end(), addToClientList);
    if (!clientIdList.empty())
        std::for_each(joinedNetworkable.begin(), joinedNetworkable.end(), update);
}
