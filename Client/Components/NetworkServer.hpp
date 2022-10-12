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
        unsigned short id;

        ///@brief Construct a new Network Server object
        ///@param Id Id of the Communicator Server
        NetworkServer(unsigned short Id = 0) : id(Id){};

        ///@brief Destroy the Network Server object
        ~NetworkServer() = default;
    };
} // namespace ecs
