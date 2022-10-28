/*
** EPITECH PROJECT, 2022
** R-Type [WSL : Ubuntu]
** File description:
** AnimationDelayComponent
*/

#ifndef ANIMATIONDELAYCOMPONENT_HPP_
#define ANIMATIONDELAYCOMPONENT_HPP_

#include <chrono>
#include "Component/Component.hpp"

namespace ecs
{
    /// @brief This component allows to know the delay between each frame of an animation.
    class AnimationDelayComponent : public Component {
      public:
        /// @brief The delay between each frame of an animation as milliseconds.
        std::chrono::duration<double> delay;

        /// @brief The default delay of the animation as milliseconds.
        const std::chrono::duration<double> baseDelay;

        /// @brief Construct the class to set default values.
        /// @param d Delay to set the baseDelay of the animation. Default value is 500.0 milliseconds.
        AnimationDelayComponent(const double &d = 500.0)
            : baseDelay(std::chrono::duration<double>(d)), delay(std::chrono::duration<double>(d)){};

        /// @brief Default destructor.
        ~AnimationDelayComponent() = default;
    };
} // namespace ecs

#endif /* !ANIMATIONDELAYCOMPONENT_HPP_ */
