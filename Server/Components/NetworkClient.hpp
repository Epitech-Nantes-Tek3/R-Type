/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** NetworkClient
*/

#pragma once

#include "Component/Component.hpp"

namespace ecs
{
    ///@brief The component which will be used to link the Communicator Client'ID
    class NetworkClient : public Component {
      public:
        ///@brief The id of the Communicator Client'ID
        std::size_t id;

        ///@brief Construct a new Network Client object
        ///@param ID ID of the Communicator Client
        NetworkClient(std::size_t ID = 0) : id(ID){};

        ///@brief Destroy the Network Client object
        ~NetworkClient() = default;
    };
} // namespace ecs
