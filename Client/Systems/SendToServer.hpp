/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** SendToServer
*/

#pragma once

#include <algorithm>
#include <concepts>
#include <map>
#include <typeindex>
#include "../Components/Controllable.hpp"
#include "../Components/NetworkServer.hpp"
#include "../Components/Networkable.hpp"
#include "GameComponents/DestinationComponent.hpp"
#include "GameComponents/EquipmentComponent.hpp"
#include "GameComponents/InvinsibleComponent.hpp"
#include "GameComponents/InvisibleComponent.hpp"
#include "GameComponents/LifeComponent.hpp"
#include "GameComponents/PositionComponent.hpp"
#include "GameComponents/VelocityComponent.hpp"
#include "World/World.hpp"

///@brief a static map which is used to know which ID is used for a component type for the RFC protocol
static const std::map<std::type_index, unsigned short> componentRFCId = {{typeid(ecs::Destination), 1},
    {typeid(ecs::Equipment), 2}, {typeid(ecs::Invinsible), 3}, {typeid(ecs::Invisible), 4}, {typeid(ecs::Life), 5},
    {typeid(ecs::Position), 6}, {typeid(ecs::Velocity), 7}};

struct SendToServer : public ecs::System {
    /// @brief A template function which is used when there is no component to send to the server.
    /// @tparam ...C The component types
    /// @param world The world that the system is running in.
    /// @param networkId The id which is common to the server and the client
    /// @param entity Entity which must be shared
    /// @param serverIdList The list of servers to which the datas must be sent
    template <std::derived_from<ecs::Component>... C>
    requires(sizeof...(C) == 0) void sendToServer(ecs::World &world, const unsigned short &networkId,
        std::shared_ptr<ecs::Entity> entity, const std::vector<unsigned short> &serverIdList) const
    {
        (void)networkId;
        (void)entity;
        (void)serverIdList;
        return;
    }

    /// @brief A template function which is used when there is at least one component to send to the server.
    /// @tparam C1 The first component type
    /// @tparam ...C2 The other component types
    /// @param world The world that the system is running in.
    /// @param networkId The id which is common to the server and the client
    /// @param entity Entity which must be shared
    /// @param serverIdList The list of servers to which the datas must be sent
    template <std::derived_from<ecs::Component> C1, std::derived_from<ecs::Component>... C2>
    void sendToServer(ecs::World &world, const unsigned short &networkId, std::shared_ptr<ecs::Entity> entity,
        const std::vector<unsigned short> &serverIdList) const
    {
        if (componentRFCId.find(typeid(C1)) != componentRFCId.end()) {
            if (entity->contains<C1>()) {
                world.getTransisthorBridge().get()->transitEcsDataToNetworkData<C1>(
                    networkId, componentRFCId.find(typeid(C1))->second, entity->getComponent<C1>(), serverIdList);
            }
        }
    }

    /// @brief For each player, send their velocity to the server
    /// @param world The world that the system is running in.
    void runSystem(ecs::World &world);

    /// @brief It runs the system
    /// @param world The world that the system is running in.
    inline void run(ecs::World &world) override final { runSystem(world); }
};
