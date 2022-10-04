/*
** EPITECH PROJECT, 2022
** Project
** File description:
** HitboxSize
*/

#ifndef HITBOXSIZE_HPP_
#define HITBOXSIZE_HPP_

#include "Component.hpp"

namespace ecs
{
    /// @brief The HitboxSize component, useful for every entity with life
    class HitboxSize : public Component {
      public:
        /// @brief The length of the HitboxSize
        int x;
        /// @brief The lenght of the HitboxSize
        int y;

        /// @brief Constructor of the HitboxSize component
        /// @param X the length
        /// @param Y the lenght
        HitboxSize(const int &X, const int &Y) : x(X), y(Y){};
        /// @brief Copy Constructor of the HitboxSize Component
        /// @param old The copy of the HitBox Component
        HitboxSize(const HitboxSize &old) : x(old.x), y(old.y) {};
        /// @brief Default Destructor
        ~HitboxSize() = default;
    };
} // namespace ecs

#endif /* !HITBOXSIZE_HPP_ */
