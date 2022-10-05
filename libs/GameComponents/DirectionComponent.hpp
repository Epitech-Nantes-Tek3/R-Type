/*
** EPITECH PROJECT, 2022
** Project
** File description:
** DirectionComponent
*/

#ifndef DIRECTIONCOMPONENT_HPP_
#define DIRECTIONCOMPONENT_HPP_

#include "Component.hpp"

namespace ecs
{
    /// @brief The Direction component, used for mobiles entities
    class Direction : public Component {
      public:
        /// @brief The orientation (abscissa) of the Direction
        int x;
        /// @brief The orientation (ordinate) of the Direction
        int y;

        /// @brief Constructor of the Direction component
        /// @param X the orientation (abscissa)
        /// @param Y the orientation (ordinate)
        Direction(const int &X, const int &Y) : x(X), y(Y){};
        /// @brief Copy Constructor of the Direction Component
        /// @param old The copy of the Direction Component
        Direction(const Direction &old) : x(old.x), y(old.y) {};
        /// @brief Default Destructor
        ~Direction() = default;
    };
} // namespace ecs

#endif /* !DirectionCOMPONENT_HPP_ */
