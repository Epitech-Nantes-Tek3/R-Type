/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** CreateWritable
*/

#ifndef CREATEWRITABLE_HPP_
#define CREATEWRITABLE_HPP_

#include "World/World.hpp"
#include "R-TypeLogic/EntityManipulation/ButtonManipulation/Components/DisplayState.hpp"

namespace ecs
{
    /// @brief This function creates a new Writable Entity with these parameters
    /// @param world The world in which the Writable must be created
    /// @param posX Position x of the Writable
    /// @param posY Position y of the Writable
    /// @param sizeX Size x of the Writable
    /// @param sizeY Size y of the Writable
    /// @param state The associated state to decide when the writable will be displayed
    /// @return Id of the new Writable in std::size_t
    std::size_t createNewWritable(World &world, const int posX, const int posY, const int sizeX, const int sizeY, MenuStates::menuState_e state);
} // namespace ecs

#endif /* !CREATEBUTTON_HPP_ */
