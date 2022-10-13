/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** TextureName
*/

#ifndef TEXTURENAME_HPP_
#define TEXTURENAME_HPP_

#include "Component/Component.hpp"
#include "GraphicsTextureResource.hpp"

namespace ecs
{

    class TextureName : public Component {
        public:
            /// @brief The texture name stores to find the corresponding textureName.
            textureName_e textureName;

            /// @brief Constructor of the TextureName component
            /// @param newTextureName The value to set in the textureName, corresponding
            /// on the sf::Texture load in shared resource GraphicsTexture.
            TextureName(textureName_e newTextureName = UNDEFINED);

            /// @brief Default destructor of TextureName component.
            ~TextureName() = default;
    };
}

#endif /* !TEXTURENAME_HPP_ */
