/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** SendToServer
*/

#include "SendToServer.hpp"
#include "R-TypeLogic/Global/Components/ControlableComponent.hpp"

using namespace transisthor::ecslogic;
using namespace rtypelogic::global;
using namespace ecs;

void SendToServer::runSystem(World &world)
{
    std::vector<std::shared_ptr<Entity>> servers = world.joinEntities<NetworkServer>();
    std::vector<std::shared_ptr<Entity>> players = world.joinEntities<Controlable>();
    std::vector<unsigned short> serverIdList;

    auto addToServerList = [&serverIdList](std::shared_ptr<Entity> entityPtr) {
        serverIdList.emplace_back(entityPtr->getComponent<NetworkServer>().id);
    };

    auto update = [this, &world, &serverIdList](std::shared_ptr<Entity> entityPtr) {
        unsigned short networkId = entityPtr->getComponent<Networkable>().id;
        sendToServer<Velocity, Position>(world, networkId, entityPtr, serverIdList);
        return;
    };

    std::for_each(servers.begin(), servers.end(), addToServerList);
    if (!serverIdList.empty()) {
        std::for_each(players.begin(), players.end(), update);
    }
}
