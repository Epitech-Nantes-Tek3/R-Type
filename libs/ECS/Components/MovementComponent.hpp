/*
** EPITECH PROJECT, 2022
** Project
** File description:
** MovementComponent
*/

#ifndef MOVEMENTCOMPONENT_HPP_
#define MOVEMENTCOMPONENT_HPP_

#include "Component.hpp"

namespace ecs
{
    /// @brief The Movement component, used for mobiles entities
    class Movement : public Component {
      public:
        /// @brief The destination (abscissa) of the Movement
        int x;
        /// @brief The destination (ordinate) of the Movement
        int y;

        /// @brief Constructor of the Movement component
        /// @param X the destination (abscissa)
        /// @param Y the destination (ordinate)
        Movement(const int &X, const int &Y) : x(X), y(Y){};
        /// @brief Copy Constructor of the Movement Component
        /// @param old The copy of the Movement Component
        Movement(const Movement &old) : x(old.x), y(old.y) {};
        /// @brief Default Destructor
        ~Movement() = default;
    };
} // namespace ecs

#endif /* !MOVEMENTCOMPONENT_HPP_ */
