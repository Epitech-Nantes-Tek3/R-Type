/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** SendToClient
*/

#include "SendToClient.hpp"
#include "Transisthor/ECSLogic/Both/Resources/SendingFrequency.hpp"

using namespace transisthor::ecslogic;
using namespace rtypelogic::global;
using namespace ecs;

void SendToClient::runSystem(World &world)
{
    std::vector<std::shared_ptr<Entity>> clients = world.joinEntities<NetworkClient>();
    std::vector<std::shared_ptr<Entity>> joinedNetworkable = world.joinEntities<Networkable>();
    std::vector<unsigned short> clientIdList;

    auto addToClientList = [&clientIdList](std::shared_ptr<Entity> entityPtr) {
        clientIdList.emplace_back(entityPtr.get()->getComponent<NetworkClient>().id);
    };

    auto update = [this, &world, &clientIdList](std::shared_ptr<Entity> entityPtr) {
        unsigned short networkId = entityPtr->getComponent<Networkable>().id;
        sendToClients<Destination, Equipment, Invinsible, Invisible, Life, Position,
            Velocity, Death>(world, networkId, entityPtr, clientIdList);
        return;
    };

    std::for_each(clients.begin(), clients.end(), addToClientList);
    if (!clientIdList.empty())
        std::for_each(joinedNetworkable.begin(), joinedNetworkable.end(), update);
}
