/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** GameStates
*/

#ifndef GAMESTATES_HPP_
#define GAMESTATES_HPP_

#include "Resource/Resource.hpp"

namespace ecs
{
    /// @brief This resource class stores the current game state of the client
    class GameStates : public Resource {
      public:
        /// @brief Enumeration of all available game states
        enum gameState_e {UNDEFINED, IN_GAME, IN_PAUSED, IN_WRITING};

        /// @brief Constructor of the resource, defining a new state
        /// @param newState The current game state to be set
        GameStates(gameState_e newState = UNDEFINED) : currentState(newState) {};

        /// @brief Default Destructor
        ~GameStates() = default;

        /// @brief The Current game State
        gameState_e currentState;
    };

} // namespace ecs

#endif /* !GAMESTATES_HPP_ */
