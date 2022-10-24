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
#include "Transisthor/TransisthorECSLogic/Both/Components/Networkable.hpp"
#include "Transisthor/TransisthorECSLogic/Server/Components/NetworkClient.hpp"
#include "World/World.hpp"
#include "R-TypeLogic/Global/Components/DeathComponent.hpp"
#include "R-TypeLogic/Global/Components/DestinationComponent.hpp"
#include "R-TypeLogic/Global/Components/EquipmentComponent.hpp"
#include "R-TypeLogic/Global/Components/InvinsibleComponent.hpp"
#include "R-TypeLogic/Global/Components/InvisibleComponent.hpp"
#include "R-TypeLogic/Global/Components/LifeComponent.hpp"
#include "R-TypeLogic/Global/Components/PositionComponent.hpp"
#include "R-TypeLogic/Global/Components/VelocityComponent.hpp"

///@brief a static map which is used to know which ID is used for a component type for the RFC protocol
static const std::map<std::type_index, unsigned short> componentRFCId = {{typeid(ecs::Destination), 1},
    {typeid(ecs::Equipment), 2}, {typeid(ecs::Invinsible), 3}, {typeid(ecs::Invisible), 4}, {typeid(ecs::Life), 5},
    {typeid(ecs::Position), 6}, {typeid(ecs::Velocity), 7}, {typeid(ecs::Death), 8}};

///@brief `SendToClient` is a system that sends Networkable Entities datas to clients
struct SendToClient : public ecs::System {
    /// @brief A template function that is used when there is no component to send to the client.
    /// @tparam ...C The component types
    /// @param world The world that the system is running in.
    /// @param networkId The id which is common to the server and the client
    /// @param entity Entity which must be shared
    /// @param clientIdList The list of clients to which the datas must be sent
    template <std::derived_from<ecs::Component>... C>
    requires(sizeof...(C) == 0) void sendToClients(ecs::World &world, const unsigned short &networkId,
        std::shared_ptr<ecs::Entity> entity, const std::vector<unsigned short> &clientIdList) const
    {
        (void)networkId;
        (void)entity;
        (void)clientIdList;
        (void)world;
        return;
    }

    /// @brief A template function that is used when there is at least one component to send to the client.
    /// @tparam C1 The first component type
    /// @tparam ...C2 The other component types
    /// @param world The world that the system is running in.
    /// @param networkId The id which is common to the server and the client
    /// @param entity Entity which must be shared
    /// @param clientIdList The list of clients to which the datas must be sent
    template <std::derived_from<ecs::Component> C1, std::derived_from<ecs::Component>... C2>
    void sendToClients(ecs::World &world, const unsigned short &networkId, std::shared_ptr<ecs::Entity> entity,
        const std::vector<unsigned short> &clientIdList) const
    {
        if (componentRFCId.find(typeid(C1)) != componentRFCId.end()) {
            if (entity->contains<C1>()) {
                C1 &component = entity->getComponent<C1>();
                if (component.modified) {
                    component.modified = false;
                    std::free(world.getTransisthorBridge().get()->transitEcsDataToNetworkData<C1>(
                        networkId, componentRFCId.find(typeid(C1))->second, component, clientIdList));
                } else if (component.sendToEveryone) {
                    component.sendToEveryone = false;
                    std::free(world.getTransisthorBridge().get()->transitEcsDataToNetworkData<C1>(
                        networkId, componentRFCId.find(typeid(C1))->second, component, clientIdList));
                }
            }
        }
        sendToClients<C2...>(world, networkId, entity, clientIdList);
    }

    /// @brief It sends the data of all the entities which have the Networkable component to all the clients
    /// @param world The world which the system is running in.
    void runSystem(ecs::World &world);

    /// @brief It runs the system
    /// @param world The world which the system is running in.
    inline void run(ecs::World &world) override final { runSystem(world); };
};
