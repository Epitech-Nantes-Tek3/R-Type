/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** NewlyCreated
*/

#ifndef NEWLYCREATED_HPP_
#define NEWLYCREATED_HPP_

#include <random>
#include <string.h>
#include "Component/Component.hpp"

namespace ecs
{
    /// @brief This component is in order to give a unique id to an entity, it's used in the sending of the creation of
    /// a entity in the client This Component is a distinctive one (used by the function
    /// updateComponentOfAnEntityFromGivenDistinctiveComponent in the world) so it must have a operator== overload
    class NewlyCreated : public Component {
      public:
        /// @brief The Entity’s unique identifier
        std::string uuid;
        /// @brief It says if the entity has been created in the server (false) or in the client (true)
        bool isClientIntance;

        /// @brief Construct a new NewlyCreated object
        /// @param newUuid The UUID
        /// @param inClient Must be true if it's in the Client instance. False otherwise.
        inline NewlyCreated(std::string newUuid = "", bool inClient = false)
            : uuid(newUuid), isClientIntance(inClient){};

        ///@brief Destroy the NewlyCreated object
        ///
        ~NewlyCreated() = default;

        /// @brief It creates an UUID.
        /// DISCLAIMER : It's not a RFC-4122-compliant UUID.
        /// @param len
        /// @return std::string
        std::string generate_uuid(std::mt19937 gen, size_t len)
        {
            const char hex_char[] = "0123456789ABCDEF";

            std::string uuid(len, '\0');

            std::uniform_int_distribution<> dis(0, sizeof(hex_char) - 2);
            for (auto &c : uuid) {
                c = hex_char[dis(gen)];
            }
            return uuid;
        }
    };

    inline bool operator==(const NewlyCreated &one, const NewlyCreated &two) { return one.uuid == two.uuid; }
} // namespace ecs
#endif /* !NEWLYCREATED_HPP_ */
