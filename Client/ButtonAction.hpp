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
void exitWindow(World &world);

/// @brief Pause the game, changing the menu state resource
/// @param world the world where the game will be paused
void pauseGame(World &world);

/// @brief Resume the game, changing the menu state resource
/// @param world the world where the game will be resumed
void resumeGame(World &world);

#endif /* !BUTTONACTION_HPP_ */
