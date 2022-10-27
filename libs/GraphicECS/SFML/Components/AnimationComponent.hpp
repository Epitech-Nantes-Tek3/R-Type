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

namespace ecs
{
    /// @brief This component stores a vector of textures to make an animation with them.
    class AnimationComponent : public Component {
        public:
            /// @brief A vector of textureName to store textures used for the animation.
            std::vector<GraphicsTextureResource::textureName_e> textures;

            /// @brief Default constructor of AnimationComponent.
            AnimationComponent() = default;

            /// @brief Default destructor of AnimationComponent.
            ~AnimationComponent() = default;
    };
}

#endif /* !ANIMATIONCOMPONENT_HPP_ */
