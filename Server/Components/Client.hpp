/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** Client
*/

#pragma once

#include "Component/Component.hpp"

namespace ecs
{
    class Client : public Component {
      public:
        std::size_t id;
        Client(std::size_t ID = 0) : id(ID){};
        ~Client() = default;
    };
} // namespace ecs
