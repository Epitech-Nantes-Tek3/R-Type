/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** NetworkServer
*/

#pragma once

#include "Component/Component.hpp"

namespace transisthor::ecslogic
{
    ///@brief The component which will be used to link the Communicator Server'ID
    class NetworkServer : public ecs::Component {
      public:
        ///@brief The id of the Communicator Server'ID
        unsigned short id;

        ///@brief Construct a new Network Server object
        ///@param newId Id of the Communicator Server
        NetworkServer(unsigned short newId = 0) : id(newId){};

        ///@brief Destroy the Network Server object
        ~NetworkServer() = default;
    };
} // namespace transisthor::ecslogic
