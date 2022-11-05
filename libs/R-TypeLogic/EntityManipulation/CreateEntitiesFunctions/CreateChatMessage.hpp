/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** CreateChatMessage
*/

#ifndef CREATECHATMESSAGE_HPP_
#define CREATECHATMESSAGE_HPP_

#include "World/World.hpp"

namespace ecs
{
    /// @brief This function creates a new ChatMessage Entity with these parameters
    /// @param world The world in which the ChatMessage must be created
    /// @param posX Position x of the ChatMessage
    /// @param posY Position y of the ChatMessage
    /// @param sizeX Size x of the ChatMessage
    /// @param sizeY Size y of the ChatMessage
    /// @param frequency time's before the message disparition
    /// @param author of the message
    /// @param content of the message
    /// @return Id of the new ChatMessage in std::size_t
    std::size_t createNewChatMessage(World &world, const int posX, const int posY, const int sizeX, const int sizeY,
        double frequency, std::string author, std::string content);
} // namespace ecs

#endif /* !CREATECHATMESSAGE_HPP_ */
