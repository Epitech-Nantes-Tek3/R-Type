/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** NetworkServer
*/

#pragma once

#include "Component/Component.hpp"

namespace ecs
{
    ///@brief The component which will be used to link the Communicator Server'ID
    class NetworkServer : public Component {
      public:
        ///@brief The id of the Communicator Server'ID
        std::size_t id;

        ///@brief Construct a new Network Server object
        ///@param ID ID of the Communicator Server
        NetworkServer(std::size_t ID = 0) : id(ID){};

        ///@brief Destroy the Network Server object
        ~NetworkServer() = default;
    };
} // namespace ecs
