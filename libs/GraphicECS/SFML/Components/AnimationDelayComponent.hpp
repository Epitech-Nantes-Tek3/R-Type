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
    class AnimationDelayComponent : public Component {
        public:
            double delay;
            AnimationDelayComponent() = default;
            ~AnimationDelayComponent() = default;
    };
} // namespace ecs

#endif /* !ANIMATIONDELAYCOMPONENT_HPP_ */
