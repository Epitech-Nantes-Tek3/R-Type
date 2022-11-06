/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** DisplayState
*/

#ifndef DISPLAYSTATE_HPP_
#define DISPLAYSTATE_HPP_

#include "Component/Component.hpp"
#include "R-TypeLogic/EntityManipulation/ButtonManipulation/SharedResources/MenuStates.hpp"

namespace ecs
{
    /// @brief This is the display Component. It's used for the Button Entities to choose the menu to be displayed
    class DisplayState : public Component {
      public:
        /// @brief The state where the associated button shall be displayed
        MenuStates::menuState_e displayState;

        /// @brief Constructor of the DisplayState Component
        /// @param newDisplayState the new state where the associated button shall be displayed
        DisplayState(MenuStates::menuState_e newDisplayState = MenuStates::UNDEFINED) : displayState(newDisplayState) {};

        /// @brief Default Destructor
        ~DisplayState() = default;

    };
} // namespace ecs

#endif /* !DISPLAYSTATE_HPP_ */
