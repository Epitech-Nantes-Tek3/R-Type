/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** GraphicsTextureResource
*/

#ifndef GRAPHICSTEXTURERESOURCE_HPP_
#define GRAPHICSTEXTURERESOURCE_HPP_

#include "Resource/Resource.hpp"
#include <SFML/Graphics.hpp>

namespace ecs
{
    /// @brief This resource class stores a Graphical SFML texture to be set on a rectangle shape resource.
    /// This class is created in order to set a texture on a rectangle shape resource.
    class GraphicsTextureResource : public Resource {
        public:
            /// @brief The graphical SFML texture to be set on a rectangle shape resource.
            sf::Texture texture;

            /// @brief Default constructor of the class.
            GraphicsTextureResource() = default;

            /// @brief Default destructor of the class.
            ~GraphicsTextureResource() = default;
    };
} // namespace

#endif /* !GRAPHICSTEXTURERESOURCE_HPP_ */