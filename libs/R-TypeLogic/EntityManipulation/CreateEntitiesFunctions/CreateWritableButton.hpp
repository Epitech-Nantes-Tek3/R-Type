/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** CreateWritableButton
*/

#ifndef CREATEWRITABLEBUTTON_HPP_
#define CREATEWRITABLEBUTTON_HPP_

#include "World/World.hpp"
#include "R-TypeLogic/EntityManipulation/ButtonManipulation/Components/ActionName.hpp"
#include "R-TypeLogic/EntityManipulation/ButtonManipulation/Components/DisplayState.hpp"
#include "R-TypeLogic/Global/Components/ButtonComponent.hpp"

namespace ecs
{
    /// @brief This function creates a new WritableButton Entity with these parameters
    /// @param world The world in which the WritableButton must be created
    /// @param posX Position x of the WritableButton
    /// @param posY Position y of the WritableButton
    /// @param sizeX Size x of the WritableButton
    /// @param sizeY Size y of the WritableButton
    /// @param actionName The action function to use for the WritableButton
    /// @param displayState The associated state to decide when the writableButton will be displayed
    /// @param associatedWritableId id of the associated writable entity
    /// @return Id of the new WritableButton in std::size_t
    std::size_t createNewWritableButton(World &world, const int posX, const int posY, const int sizeX, const int sizeY,
        std::function<void(World &, Entity &, std::string &)> actionFunction, MenuStates::menuState_e state, std::size_t associatedWritableId);
} // namespace ecs

#endif /* !CREATEWRITABLEBUTTON_HPP_ */
