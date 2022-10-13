/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** SendToServer
*/

#include "SendToServer.hpp"

void SendToServer::runSystem(ecs::World &world)
{
    std::vector<std::shared_ptr<ecs::Entity>> servers = world.joinEntities<ecs::NetworkServer>();
    std::vector<std::shared_ptr<ecs::Entity>> players = world.joinEntities<ecs::Controllable>();
    std::vector<unsigned short> serverIdList;

    auto addToServerList = [&serverIdList](std::shared_ptr<ecs::Entity> entityPtr) {
        serverIdList.emplace_back(entityPtr->getComponent<ecs::NetworkServer>().id);
    };

    auto update = [this, &world, &serverIdList](std::shared_ptr<ecs::Entity> entityPtr) {
        unsigned short networkId = entityPtr->getComponent<ecs::Networkable>().id;
        sendToServer<ecs::Velocity>(world, networkId, entityPtr, serverIdList);
        return entityPtr;
    };

    std::for_each(servers.begin(), servers.end(), addToServerList);
    std::for_each(players.begin(), players.end(), update);
}