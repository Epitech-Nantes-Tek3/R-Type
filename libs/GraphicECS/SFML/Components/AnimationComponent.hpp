/*
** EPITECH PROJECT, 2022
** R-Type [WSL : Ubuntu]
** File description:
** AnimationComponent
*/

#ifndef ANIMATIONCOMPONENT_HPP_
#define ANIMATIONCOMPONENT_HPP_

#include <vector>
#include "Component/Component.hpp"
#include "GraphicECS/SFML/Resources/GraphicsTextureResource.hpp"
#include "GraphicsTextureResource.hpp"

namespace graphicECS::SFML::Components
{
    /// @brief This component stores a vector of textures to make an animation with them.
    class AnimationComponent : public ecs::Component {
      public:
        /// @brief A vector of textureName to store textures used for the animation.
        std::vector<graphicECS::SFML::Resources::GraphicsTextureResource::textureName_e> textures;

            /// @brief Index of the current texture in use.
            graphicECS::SFML::Resources::GraphicsTextureResource::textureName_e currentTexture;

            /// @brief Default constructor of AnimationComponent.
            AnimationComponent() = default;

        /// @brief Default destructor of AnimationComponent.
        ~AnimationComponent() = default;
    };
} // namespace graphicECS::SFML::Components

#endif /* !ANIMATIONCOMPONENT_HPP_ */
