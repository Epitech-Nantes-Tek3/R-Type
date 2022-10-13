/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** GraphicsRectangleComponent
*/

#include "GraphicsRectangleComponent.hpp"

using namespace ecs;

GraphicsRectangleComponent::GraphicsRectangleComponent(const std::size_t x, const std::size_t y, const std::size_t width, const std::size_t height)
{
    shape.setPosition(x, y);
    shape.setSize(sf::Vector2f(width, height));
}
