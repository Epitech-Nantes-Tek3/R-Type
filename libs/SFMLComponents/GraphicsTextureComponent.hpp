/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** GraphicsTextureComponent
*/

#ifndef GRAPHICSTEXTURECOMPONENT_HPP_
#define GRAPHICSTEXTURECOMPONENT_HPP_

#include "Component/Component.hpp"
#include <SFML/Graphics.hpp>

namespace ecs
{
    /// @brief This component class stores a Graphical SFML texture to be set on a rectangle shape component.
    /// This class is created in order to set a texture on a rectangle shape component.
    class GraphicsTextureComponent : public Component {
        public:
            /// @brief The graphical SFML texture to be set on a rectangle shape component.
            sf::Texture texture;

            /// @brief Default constructor of the class.
            GraphicsTextureComponent() = default;

            /// @brief Default destructor of the class.
            ~GraphicsTextureComponent() = default;
    };
} // namespace

#endif /* !GRAPHICSTEXTURECOMPONENT_HPP_ */
