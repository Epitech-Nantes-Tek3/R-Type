/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** SendToClient
*/

#pragma once

#include <algorithm>
#include <concepts>
#include <map>
#include <typeindex>
#include "../Components/NetworkClient.hpp"
#include "../Components/Networkable.hpp"
#include "World/World.hpp"

#include "GameComponents/DestinationComponent.hpp"
#include "GameComponents/EquipmentComponent.hpp"
#include "GameComponents/InvinsibleComponent.hpp"
#include "GameComponents/InvisibleComponent.hpp"
#include "GameComponents/LifeComponent.hpp"
#include "GameComponents/PositionComponent.hpp"
#include "GameComponents/VelocityComponent.hpp"

static const std::map<std::type_index, std::size_t> componentRFCId = {{typeid(ecs::Destination), 1},
    {typeid(ecs::Equipment), 2}, {typeid(ecs::Invinsible), 3}, {typeid(ecs::Invisible), 4}, {typeid(ecs::Life), 5},
    {typeid(ecs::Position), 6}, {typeid(ecs::Velocity), 7}};

struct SendToClient : public ecs::System {
    template <std::derived_from<ecs::Component>... C>
    requires(sizeof...(C) == 0) void sendToClients(ecs::World &world, const std::size_t &networkId, ecs::Entity *entity,
        const std::vector<std::size_t> &clientIdList) const
    {
        (void)networkId;
        (void)entity;
        (void)clientIdList;
        return;
    }

    template <std::derived_from<ecs::Component> C1, std::derived_from<ecs::Component>... C2>
    void sendToClients(ecs::World &world, const std::size_t &networkId, ecs::Entity *entity,
        const std::vector<std::size_t> &clientIdList) const
    {
        std::map<std::type_index, std::size_t>::const_iterator it = componentRFCId.find(typeid(C1));
        if (it != componentRFCId.end()) {
            if (entity->contains<C1>()) {
                (void)clientIdList;
                world.getTransisthorBridge().get()->transitEcsDataToNetworkData<C1>(networkId, it->second, entity->getComponent<C1>());
                // send clientIdList later when it will be implemented
            }
        }
    }

    void run(ecs::World &world) override final
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
};
