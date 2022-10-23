/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** NetworkClient
*/

#pragma once

#include "Component/Component.hpp"

namespace transisthor::ecslogic
{
    ///@brief The component which will be used to link the Communicator Client'ID
    class NetworkClient : public ecs::Component {
      public:
        ///@brief The id of the Communicator Client'ID
        unsigned short id;

        ///@brief Construct a new Network Client object
        ///@param newId ID of the Communicator Client
        NetworkClient(unsigned short newId = 0) : id(newId){};

        ///@brief Destroy the Network Client object
        ~NetworkClient() = default;
    };
} // namespace transisthor::ecslogic
