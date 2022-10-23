/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** ParallaxComponent
*/

#ifndef PARALLAXCOMPONENT_HPP_
#define PARALLAXCOMPONENT_HPP_

#include "Component/Component.hpp"

namespace graphic::sfml
{
    /// @brief This component class create a sprite wich travel in the background
    class ParallaxBackground : public ecs::Component {};
} // namespace graphic::sfml

#endif /* !PARALLAXCOMPONENT_HPP_ */
