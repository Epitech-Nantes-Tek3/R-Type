/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** CreateText
*/

#ifndef CREATETEXT_HPP_
#define CREATETEXT_HPP_

#include "World/World.hpp"
#include "R-TypeLogic/EntityManipulation/ButtonManipulation/Components/DisplayState.hpp"
#include "R-TypeLogic/Global/Components/LayerLvL.hpp"

namespace ecs
{
    /// @brief This function creates a new Text Entity with these parameters
    /// @param world The world in which the Text must be created
    /// @param posX Position x of the Text
    /// @param posY Position y of the Text
    /// @param layerLvl The button layer level, useful for graphical part
    /// @param state The associated state to decide when the button will be displayed
    /// @param text The text to be set.
    /// @return Id of the new Text in std::size_t
    std::size_t createNewText(World &world, const int posX, const int posY, LayerLvL::layer_e layerLvl,
        MenuStates::menuState_e state, const std::string &text);
} // namespace ecs

#endif /* !CREATETEXT_HPP_ */
