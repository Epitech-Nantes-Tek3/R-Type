/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** GraphicsTextComponent
*/

#ifndef GRAPHICSTEXTCOMPONENT_HPP_
#define GRAPHICSTEXTCOMPONENT_HPP_

#include "Component/Component.hpp"
#include <SFML/Graphics.hpp>

namespace ecs
{
    /// @brief This component class stores a Graphical SFML text.
    /// This class is created in order to draw a text on a screen, specified in shared resource as a window.
    class GraphicsTextComponent : public Component {
        public:
            /// @brief The Graphical SFML text to be rendered.
            /// @note It needs a font component to be drawn.
            sf::Text text;

            /// @brief Default constructor of the class.
            GraphicsTextComponent() = default;

            /// @brief Default destructor of the class.
            ~GraphicsTextComponent() = default;
    };
} // namespace ecs

#endif /* !GRAPHICSTEXTCOMPONENT_HPP_ */
