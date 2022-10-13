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
    /// Each one has a unique ID.
    class Networkable : public Component {
      public:
        /// @brief The Entity’s common unique identifier
        unsigned short id;

        ///@brief Construct a new Networkable object
        ///@param newId The Entity’s common unique identifier
        Networkable(unsigned short newId = 0) : id(newId){};

        ///@brief Destroy the Networkable object
        ///
        ~Networkable() = default;
    };
} // namespace ecs
