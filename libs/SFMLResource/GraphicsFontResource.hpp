/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** GraphicsFontComponent
*/

#ifndef GRAPHICSFONTRESOURCE_HPP_
#define GRAPHICSFONTRESOURCE_HPP_

#include "Resource/Resource.hpp"
#include <SFML/Graphics.hpp>

namespace ecs
{
    /// @brief This resource class stores the font in order to draw a Graphical text resource.
    /// It justs exist for the Graphical text resource.
    class GraphicsFontResource : public Resource {
        public:
            /// @brief The Graphical SFML font to be used with Graphical text resource.
            /// @note Only used with Graphical text resource.
            sf::Font font;

            /// @brief Default constructor of the class.
            GraphicsFontResource() = default;

            /// @brief Default destructor of the class.
            ~GraphicsFontResource() = default;
    };
} // namespace

#endif /* !GRAPHICSFONTRESOURCE_HPP_ */
