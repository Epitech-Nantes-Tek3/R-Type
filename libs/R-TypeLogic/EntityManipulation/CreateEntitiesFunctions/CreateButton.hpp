/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** CreateButton
*/

#ifndef CREATEBUTTON_HPP_
#define CREATEBUTTON_HPP_

#include "GraphicECS/SFML/Components/GraphicsRectangleComponent.hpp"
#include "GraphicECS/SFML/Components/TextureName.hpp"
#include "World/World.hpp"
#include "R-TypeLogic/Global/Components/ActionName.hpp"
#include "R-TypeLogic/Global/Components/ButtonComponent.hpp"

namespace ecs
{
    /// @brief This function creates a new Button Entity with these parameters
    /// @param world The world in which the Button must be created
    /// @param posX Position x of the Button
    /// @param posY Position y of the Button
    /// @param sizeX Size x of the Button
    /// @param sizeY Size y of the Button
    /// @param textureName The Texture to be set for the Button
    /// @param actionName The action name to be set for the Button
    /// @return Id of the new Button in std::size_t
    std::size_t createNewButton(World &world, const int posX, const int posY, const int sizeX, const int sizeY,
        GraphicsTextureResource::textureName_e textureName, ButtonActionMap::buttonAction_e actionName);
} // namespace ecs

#endif /* !CREATEBUTTON_HPP_ */
