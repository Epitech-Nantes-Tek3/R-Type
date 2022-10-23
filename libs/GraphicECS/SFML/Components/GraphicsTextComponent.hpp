/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** GraphicsTextComponent
*/

#ifndef GRAPHICSTEXTCOMPONENT_HPP_
#define GRAPHICSTEXTCOMPONENT_HPP_

#include <SFML/Graphics.hpp>
#include "Component/Component.hpp"

namespace ecs
{
    /// @brief This component class stores a Graphical SFML text.
    /// This class is created in order to draw a text on a screen, specified in shared resource as a window.
    class GraphicsTextComponent : public Component {
      public:
        /// @brief The Graphical SFML text to be rendered.
        /// @note It needs a font component to be drawn.
        sf::Text text;

        /// @brief Construct a GraphicsTextComponent width default parameters if they aren't specified.
        /// @param newText The new text of the component. Default "".
        /// @param x The x position of the text on the window. Default 10.
        /// @param y The y position of the text on the window. Default 10.
        /// @param size The character size of the text. Default 16.
        GraphicsTextComponent(const std::string newText = "", const std::size_t x = 10, const std::size_t y = 10,
            const std::size_t size = 16);

        /// @brief Default destructor of the class.
        ~GraphicsTextComponent() = default;
    };
} // namespace ecs

#endif /* !GRAPHICSTEXTCOMPONENT_HPP_ */
