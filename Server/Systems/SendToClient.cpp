/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** SendToClient
*/

#include "SendToClient.hpp"

void SendToClient::run(ecs::World &world)
{
    std::vector<std::shared_ptr<ecs::Entity>> clients = world.joinEntities<ecs::NetworkClient>();
    std::vector<std::shared_ptr<ecs::Entity>> joinedNetworkable = world.joinEntities<ecs::Networkable>();
    std::vector<std::size_t> clientIdList;

    auto addToClientList = [&clientIdList](std::shared_ptr<ecs::Entity> entityPtr) {
        clientIdList.emplace_back(entityPtr.get()->getComponent<ecs::NetworkClient>().id);
    };

    auto update = [this, &world, &clientIdList](std::shared_ptr<ecs::Entity> entityPtr) {
        ecs::Entity *entity = entityPtr.get();
        std::size_t networkId = entity->getComponent<ecs::Networkable>().id;
        sendToClients<ecs::Destination, ecs::Equipment, ecs::Invinsible, ecs::Invisible, ecs::Life, ecs::Position,
            ecs::Velocity>(world, networkId, entity, clientIdList);
        return entityPtr;
    };

    std::for_each(clients.begin(), clients.end(), addToClientList);
    std::for_each(joinedNetworkable.begin(), joinedNetworkable.end(), update);
}