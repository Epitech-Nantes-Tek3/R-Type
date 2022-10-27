/*
** EPITECH PROJECT, 2022
** R-Type [WSL : Ubuntu]
** File description:
** AnimationDelayComponent
*/

#ifndef ANIMATIONDELAYCOMPONENT_HPP_
#define ANIMATIONDELAYCOMPONENT_HPP_

#include "Component/Component.hpp"

namespace ecs
{
    /// @brief This component allow to know the delay between each frame of an animation.
    class AnimationDelayComponent : public Component {
        public:
            /// @brief The delay between each frame of an animation as miliseconds.
            double delay;

            /// @brief Default constructor.
            AnimationDelayComponent() = default;

            /// @brief Default destructor.
            ~AnimationDelayComponent() = default;
    };
} // namespace ecs

#endif /* !ANIMATIONDELAYCOMPONENT_HPP_ */
