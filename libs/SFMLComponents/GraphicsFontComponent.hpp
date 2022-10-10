/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** GraphicsFontComponent
*/

#ifndef GRAPHICSFONTCOMPONENT_HPP_
#define GRAPHICSFONTCOMPONENT_HPP_

#include "Component/Component.hpp"
#include <SFML/Graphics.hpp>

namespace ecs
{
    /// @brief This component class stores the font in order to draw a Graphical text component.
    /// It justs exist for the Graphical text component.
    class GraphicsFontComponent : public Component {
        public:
            /// @brief The Graphical SFML font to be used with Graphical text component.
            /// @note Only used with Graphical text component.
            sf::Font font;

            /// @brief Default constructor of the class.
            GraphicsFontComponent() = default;

            /// @brief Default destructor of the class.
            ~GraphicsFontComponent() = default;
    };
} // namespace

#endif /* !GRAPHICSFONTCOMPONENT_HPP_ */
