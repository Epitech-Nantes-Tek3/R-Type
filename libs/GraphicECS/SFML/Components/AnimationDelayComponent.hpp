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

namespace graphicECS::SFML::Components
{
    /// @brief This component allows to know the delay between each frame of an animation.
    class AnimationDelayComponent : public ecs::Component {
      public:
        /// @brief The delay between each frame of an animation as milliseconds.
        std::chrono::duration<double> delay;

        /// @brief The default delay of the animation as milliseconds.
        std::chrono::duration<double> baseDelay;

        /// @brief Construct the class to set default values.
        /// @param d Delay to set the baseDelay of the animation. Default value is 500.0 milliseconds.
        AnimationDelayComponent(const double &d = 500.0)
            : delay(std::chrono::duration<double>(d)), baseDelay(std::chrono::duration<double>(d)){};

        /// @brief Default destructor.
        ~AnimationDelayComponent() = default;
    };
} // namespace graphicECS::SFML::Components

#endif /* !ANIMATIONDELAYCOMPONENT_HPP_ */
