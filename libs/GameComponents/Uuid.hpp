/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** Uuid
*/

#pragma once

#include <random>
#include <string.h>
#include "Component/Component.hpp"

namespace ecs
{
    /// @brief This component is in order to give a unique id to an entity, it's used in the sending of the creation of
    /// a entity in the client This Component is a distinctive one (used by the function
    /// updateComponentOfAnEntityFromGivenDistinctiveComponent in the world) so it must have a operator== overload
    class Uuid : public Component {
      public:
        /// @brief The Entity’s unique identifier
        std::string uuid;

        /// @brief Construct a new Uuid object
        /// @param uuidLen The len of the UUID
        Uuid(std::mt19937 gen = std::mt19937(std::random_device()()), unsigned short uuidLen = 16) :  uuid(_generate_uuid(gen, uuidLen)){};

        ///@brief Destroy the Uuid object
        ///
        ~Uuid() = default;

      private:
        /// @brief It creates an UUID.
        /// DISCLAIMER : It's not a RFC-4122-compliant UUID.
        /// @param len
        /// @return std::string
        static std::string _generate_uuid(std::mt19937 gen, size_t len)
        {
            static const char hex_char[] = "0123456789ABCDEF";

            std::string uuid(len, '\0');

            std::uniform_int_distribution<> dis(0, sizeof(hex_char) - 2);
            for (auto &c : uuid) {
                c = hex_char[dis(gen)];
            }
            return uuid;
        }
    };

    inline bool operator==(const Uuid &one, const Uuid &two) { return one.uuid == two.uuid; }
} // namespace ecs
