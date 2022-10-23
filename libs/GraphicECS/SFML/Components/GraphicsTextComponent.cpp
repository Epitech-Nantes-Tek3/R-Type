/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** GraphicsTextComponent
*/

#include "GraphicsTextComponent.hpp"

using namespace graphic::sfml;

GraphicsTextComponent::GraphicsTextComponent(
    const std::string newText, const std::size_t x, const std::size_t y, const std::size_t size)
{
    text.setString(newText);
    text.setPosition(x, y);
    text.setCharacterSize(size);
}
