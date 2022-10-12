/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** GraphicsRectangleComponent
*/

#ifndef GRAPHICSRECTANGLECOMPONENT_HPP_
#define GRAPHICSRECTANGLECOMPONENT_HPP_

#include "Component/Component.hpp"
#include <SFML/Graphics.hpp>

namespace ecs
{
    /// @brief This component class stores a Graphical SFML rectangle shape.
    /// This class is created in order to draw a rectangle shape on a screen.
    class GraphicsRectangleComponent : public Component {
        public:
            /// @brief The Graphical SFML rectangle shape to be rendered.
            sf::RectangleShape shape;

            /// @brief Default constructor of the class.
            GraphicsRectangleComponent(const std::size_t x = 10, const std::size_t y = 10, const std::size_t width = 10, const std::size_t height = 10);

            /// @brief Default destructor of the class.
            ~GraphicsRectangleComponent() = default;
    };
} // namespace ecs

#endif /* !GRAPHICSRECTANGLECOMPONENT_HPP_ */
