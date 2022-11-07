/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** MenuStates
*/

#ifndef MENUSTATES_HPP_
#define MENUSTATES_HPP_

#include "Resource/Resource.hpp"

namespace ecs
{
    /// @brief This resource class stores the current menu state of the client
    class MenuStates : public Resource {
      public:
        /// @brief Enumeration of all available menu states
        enum menuState_e {UNDEFINED, IN_GAME, GAME_PAUSED, MAIN_MENU };

        /// @brief Constructor of the resource, defining a new state
        /// @param newState The current menu state to be set
        MenuStates(menuState_e newState = UNDEFINED) : currentState(newState) {};

        /// @brief Default Destructor
        ~MenuStates() = default;

        /// @brief The Current Menu State
        menuState_e currentState;
    };

} // namespace ecs

#endif /* !MENUSTATES_HPP_ */
