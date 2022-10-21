/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** TextureName
*/

#ifndef TEXTURENAME_HPP_
#define TEXTURENAME_HPP_

#include "Component/Component.hpp"
#include "GraphicECS/SFMLResource/GraphicsTextureResource.hpp"

namespace ecs
{
    /// @brief TextureName store the key as enum to the corresponding texture stores in shared resource.
    class TextureName : public Component {
      public:
        /// @brief The texture name stores to find the corresponding textureName.
        GraphicsTextureResource::textureName_e textureName;

        /// @brief Constructor of the TextureName component
        /// @param newTextureName The value to set in the textureName, corresponding
        /// on the sf::Texture load in shared resource GraphicsTexture.
        TextureName(GraphicsTextureResource::textureName_e newTextureName = GraphicsTextureResource::UNDEFINED)
            : textureName(newTextureName){};

        /// @brief Default destructor of TextureName component.
        ~TextureName() = default;
    };
} // namespace ecs

#endif /* !TEXTURENAME_HPP_ */
