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
#include "Transisthor/ECSLogic/Both/Components/Networkable.hpp"
#include "Transisthor/ECSLogic/Client/Components/Controllable.hpp"
#include "Transisthor/ECSLogic/Client/Components/NetworkServer.hpp"
#include "World/World.hpp"
#include "R-TypeLogic/Global/Components/DeathComponent.hpp"
#include "R-TypeLogic/Global/Components/DestinationComponent.hpp"
#include "R-TypeLogic/Global/Components/EquipmentComponent.hpp"
#include "R-TypeLogic/Global/Components/InvinsibleComponent.hpp"
#include "R-TypeLogic/Global/Components/InvisibleComponent.hpp"
#include "R-TypeLogic/Global/Components/LifeComponent.hpp"
#include "R-TypeLogic/Global/Components/PositionComponent.hpp"
#include "R-TypeLogic/Global/Components/VelocityComponent.hpp"

using namespace rtypelogic::global;

///@brief a static map which is used to know which ID is used for a component type for the RFC protocol
static const std::map<std::type_index, unsigned short> componentRFCId = {{typeid(Destination), 1},
    {typeid(Equipment), 2}, {typeid(Invinsible), 3}, {typeid(Invisible), 4}, {typeid(Life), 5},
    {typeid(Position), 6}, {typeid(Velocity), 7}, {typeid(Death), 8}};

namespace transisthor::ecslogic
{
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
            (void)world;
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
                    C1 &component = entity->getComponent<C1>();
                    if (component.modified) {
                        component.modified = false;
                        component.sendToEveryone = true;
                        world.getTransisthorBridge().get()->transitEcsDataToNetworkData<C1>(
                            networkId, componentRFCId.find(typeid(C1))->second, component, serverIdList);
                    }
                }
            }
            sendToServer<C2...>(world, networkId, entity, serverIdList);
        }

        /// @brief For each player, send their velocity to the server
        /// @param world The world that the system is running in.
        void runSystem(ecs::World &world);

        /// @brief It runs the system
        /// @param world The world that the system is running in.
        inline void run(ecs::World &world) override final { runSystem(world); }
    };
} // namespace transisthor::ecslogic
