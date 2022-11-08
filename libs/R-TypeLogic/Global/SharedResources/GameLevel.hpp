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
    /// @brief Shared Resource game level, used to decide the current level of the game
    class GameLevel : public Resource {
      public:
        /// @brief Enumeration of all possibles level states on the game
        enum level_e { LEVEL_ONE = 0, LEVEL_TWO = 10, LEVEL_THREE = 24, LEVEL_FORTH = 40, LEVEL_INFINITE = 60 };
        /// @brief Create the GameLevel Resource
        GameLevel() : _currLevel(GameLevel::LEVEL_ONE), _waveChanged(true), _hasLevelChanged(false), _nbkills(0){};

        /// @brief Get the current level of the game
        /// @return the level of the game
        inline GameLevel::level_e getCurrentLevel() const { return this->_currLevel; };

        /// @brief Check if the game background should change
        /// @return true if the background should change, false otherwise
        inline bool hasLevelChanged() const { return this->_hasLevelChanged; };

        /// @brief State that the background has changed because the background modification
        inline void levelHasChanged() { this->_hasLevelChanged = false; };

        /// @brief Check if the mob wave should change
        /// @return true if the mob wave should change, false otherwise
        inline bool hasWaveChanged() const { return this->_waveChanged; };

        /// @brief State that the wave has changed because the mob generation has been launched
        inline void waveHasChanged() { this->_waveChanged = false; };

        /// @brief Add new kills to the private value, increase the level if necessary
        /// @param newKills the number of new kills
        void addNewKills(unsigned int newKills = 1);

        /// @brief Default destructor
        ~GameLevel() = default;

      private:
        /// @brief The current level of the game
        GameLevel::level_e _currLevel;

        /// @brief Is true if all the mob in the current wave have been killed, otherwise false
        bool _waveChanged;

        /// @brief Is true if the level has recently changed, otherwise false
        bool _hasLevelChanged;

        /// @brief The number of kills in the room by all the players
        unsigned int _nbkills;
    };
} // namespace ecs

#endif /* !GAMELEVEL_HPP_ */
