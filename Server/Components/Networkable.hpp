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
    /// @brief This component is used to know which entities must be the same in the server and in client.
    /// Each one as a unique ID.
    class Networkable : public Component {
      public:
        /// @brief The Entity’s common unique identifier
        std::size_t id;

        ///@brief Construct a new Networkable object
        ///@param ID The Entity’s common unique identifier
        Networkable(std::size_t Id = 0) : id(Id){};

        ///@brief Destroy the Networkable object
        ///
        ~Networkable() = default;
    };
} // namespace ecs
