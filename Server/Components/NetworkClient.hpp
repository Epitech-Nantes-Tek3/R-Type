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
    class NetworkClient : public Component {
      public:
        std::size_t id;
        NetworkClient(std::size_t ID = 0) : id(ID){};
        ~NetworkClient() = default;
    };
} // namespace ecs
