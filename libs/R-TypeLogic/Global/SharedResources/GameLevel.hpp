/*
** EPITECH PROJECT, 2022
** Project
** File description:
** GameLevel
*/

#ifndef GAMELEVEL_HPP_
#define GAMELEVEL_HPP_

#include "Resource/Resource.hpp"

namespace ecs
{
    /// @brief Shared Resource game level, use to decided the current level of the game
    class GameLevel : public Resource {
      public:
        /// @brief Enumeration of all possibles level states on the game
        enum level_e {
            LEVEL_ONE = 0,
            LEVEL_TWO = 10,
            LEVEL_THREE = 25,
            LEVEL_FORTH = 50,
            INFINITE = 100
        };
        /// @brief Create the GameLevel Resource
        GameLevel() : _currLevel(LEVEL_ONE), _hasLevelChanged(true), _nbkills(0) {};

        /// @brief Default destructor
        ~GameLevel() = default;

      private:
        /// @brief The current level of the game
        level_e _currLevel;

        /// @brief Is true if the level has recently changed, otherwise false
        bool _hasLevelChanged;

        /// @brief The number of kills in the room by all the players
        unsigned int _nbkills;
    };
} // namespace ecs

#endif /* !GAMELEVEL_HPP_ */
