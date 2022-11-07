/*
** EPITECH PROJECT, 2022
** R-Type
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
        enum level_e { LEVEL_ONE = 0, LEVEL_TWO = 10, LEVEL_THREE = 20, LEVEL_FORTH = 40, INFINITE = 50};
        /// @brief Create the GameLevel Resource
        GameLevel() : _currLevel(GameLevel::LEVEL_ONE), _hasLevelChanged(true), _nbkills(0){};

        /// @brief Get the current level of the game
        /// @return the level of the game
        inline GameLevel::level_e getCurrentLevel() { return this->_currLevel; };

        /// @brief Check if the game level has changed
        /// @return true if the level has change, false otherwise
        inline bool hasLevelChanged() { return this->_hasLevelChanged; };

        /// @brief State that the level has changed because mob have been generated
        inline void levelHasChanged() { this->_hasLevelChanged = false; };

        /// @brief Add new kills to the private value, increase the level if necessary
        /// @param newKills the number of new kills
        void addNewKills(unsigned int newKills = 1);

        /// @brief Default destructor
        ~GameLevel() = default;

      private:
        /// @brief The current level of the game
        GameLevel::level_e _currLevel;

        /// @brief Is true if the level has recently changed, otherwise false
        bool _hasLevelChanged;

        /// @brief The number of kills in the room by all the players
        unsigned int _nbkills;
    };
} // namespace ecs

#endif /* !GAMELEVEL_HPP_ */
