/*
** EPITECH PROJECT, 2022
** Project
** File description:
** ButtonAction
*/

#ifndef BUTTONACTION_HPP_
#define BUTTONACTION_HPP_

#include "World/World.hpp"

/// @brief Exit the windows by disconecting the client
/// @param world the world where the window will be closed
/// @param entityPtr the entity whoe's actioned the called
void exitWindow(World &world, Entity &entityPtr);

/// @brief Pause the game, changing the menu state resource
/// @param world the world where the game will be paused
/// @param entityPtr the entity whoe's actioned the called
void pauseGame(World &world, Entity &entityPtr);

/// @brief Resume the game, changing the menu state resource
/// @param world the world where the game will be resumed
/// @param entityPtr the entity whoe's actioned the called
void resumeGame(World &world, Entity &entityPtr);

/// @brief Select a writable entity, add / remove a selected component
/// @param world the world where the entity his
/// @param entityPtr the entity whoe's actioned the called
void selectAWritable(World &world, Entity &entityPtr);

/// @brief Get the content of associated writable entity and called the action function
/// @param world the world where the entity his
/// @param entityPtr the entity whoe's actioned the called
void writableButtonAction(World &world, Entity &entityPtr);

#endif /* !BUTTONACTION_HPP_ */
