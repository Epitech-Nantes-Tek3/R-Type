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
    /// This Component is a distinctive one (used by the function
    /// updateComponentOfAnEntityFromGivenDistinctiveComponent in the world) so it must have a operator== overload
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

    inline bool operator==(const Networkable &one, const Networkable &two) { return one.id == two.id; }
} // namespace ecs
