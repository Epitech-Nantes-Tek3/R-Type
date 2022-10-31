/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** PlayerComponent
*/

#ifndef PLAYERCOMPONENT_HPP_
#define PLAYERCOMPONENT_HPP_

#include "Component/Component.hpp"

namespace ecs
{
    /// @brief Player Component allows an entity to be used as a Player
    class Player : public Component {
      public:
        /// @brief Identification number for knowing wich player is
        unsigned short playerIdentifier;

        /// @brief Name of the player
        std::string name;

        /// @brief Construct a new player object
        /// @param playerIdentity Identification number of the player
        Player(unsigned short playerIdentity = 0, std::string playerName = "") : playerIdentifier(playerIdentity), name(playerName){};
    };
} // namespace ecs

#endif /* !PLAYERCOMPONENT_HPP_ */
