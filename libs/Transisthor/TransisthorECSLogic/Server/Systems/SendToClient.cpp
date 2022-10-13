/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** SendToClient
*/

#include "SendToClient.hpp"

void SendToClient::runSystem(ecs::World &world)
{
    std::vector<std::shared_ptr<ecs::Entity>> clients = world.joinEntities<ecs::NetworkClient>();
    std::vector<std::shared_ptr<ecs::Entity>> joinedNetworkable = world.joinEntities<ecs::Networkable>();
    std::vector<unsigned short> clientIdList;

    auto addToClientList = [&clientIdList](std::shared_ptr<ecs::Entity> entityPtr) {
        clientIdList.emplace_back(entityPtr.get()->getComponent<ecs::NetworkClient>().id);
    };

    auto update = [this, &world, &clientIdList](std::shared_ptr<ecs::Entity> entityPtr) {
        unsigned short networkId = entityPtr->getComponent<ecs::Networkable>().id;
        sendToClients<ecs::Destination, ecs::Equipment, ecs::Invinsible, ecs::Invisible, ecs::Life, ecs::Position,
            ecs::Velocity>(world, networkId, entityPtr, clientIdList);
        return;
    };

    std::for_each(clients.begin(), clients.end(), addToClientList);
    if (clientIdList.size())
        std::for_each(joinedNetworkable.begin(), joinedNetworkable.end(), update);
}
