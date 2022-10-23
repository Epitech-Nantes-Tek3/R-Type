/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** NetworkableIdGenerator
*/

#pragma once

#include "Resource/Resource.hpp"

namespace transisthor::ecslogic
{
    /// @brief Shared resource networkable id generator for Networkable Component
    class NetworkableIdGenerator : public ecs::Resource {
      public:
        /// @brief Construct a new Networkable Id Generator object
        NetworkableIdGenerator() : _nextId(){};

        /// @brief Destroy the Networkable Id Generator object
        ~NetworkableIdGenerator() = default;

        /// @brief Generate a new Networkable Id
        /// @return unsigned short This return the unique networkable Id to use
        inline unsigned short generateNewNetworkableId()
        {
            _nextId++;
            return _nextId;
        };

      private:
        /// @brief The next networkable id
        unsigned short _nextId;
    };
} // namespace transisthor::ecslogic
