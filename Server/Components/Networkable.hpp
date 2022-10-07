/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** Networkable
*/

#pragma once

#include "Component/Component.hpp"

namespace ecs
{
    class Networkable : public Component {
      public:
        std::size_t id;
        Networkable(std::size_t ID = 0) : id(ID){};
        ~Networkable() = default;
    };
} // namespace ecs
