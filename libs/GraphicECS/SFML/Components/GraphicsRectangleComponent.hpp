/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** GraphicsRectangleComponent
*/

#ifndef GRAPHICSRECTANGLECOMPONENT_HPP_
#define GRAPHICSRECTANGLECOMPONENT_HPP_

#include <SFML/Graphics.hpp>
#include "Component/Component.hpp"

namespace graphicECS::SFML::Components
{
    /// @brief This component class stores a Graphical SFML rectangle shape.
    /// This class is created in order to draw a rectangle shape on a screen.
    class GraphicsRectangleComponent : public Component {
      public:
        /// @brief The Graphical SFML rectangle shape to be rendered.
        sf::RectangleShape shape;

        /// @brief Construct a GraphicsRectanbleComponent with default parameters if they aren't specified.
        /// @param x The x position of the shape on the window. Default 10.
        /// @param y The y position of the shape on the window. Default 10.
        /// @param width The width size of the shape on the window. Default 10.
        /// @param height The height size of the shape on the window. Default 10.
        GraphicsRectangleComponent(const std::size_t x = 10, const std::size_t y = 10, const std::size_t width = 10,
            const std::size_t height = 10);

        /// @brief Default destructor of the class.
        ~GraphicsRectangleComponent() = default;
    };
} // namespace graphicECS::SFML::Components

#endif /* !GRAPHICSRECTANGLECOMPONENT_HPP_ */
