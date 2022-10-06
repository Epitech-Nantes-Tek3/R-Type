/*
** EPITECH PROJECT, 2022
** Project
** File description:
** PositionComponent
*/

#ifndef POSITIONCOMPONENT_HPP_
#define POSITIONCOMPONENT_HPP_

#include "Component/Component.hpp"

namespace ecs
{
    /// @brief The Position component, almost used for every entities
    class Position : public Component {
      public:
        /// @brief The abscissa of the Position
        int x;
        /// @brief The ordinate of the Position
        int y;

        /// @brief Constructor of the Position component
        /// @param X the abscissa
        /// @param Y the ordinate
        Position(const int &X, const int &Y) : x(X), y(Y){};
        /// @brief Copy Constructor of the Position Component
        /// @param old The copy of the Position Component
        Position(const Position &old) : x(old.x), y(old.y) {};
        /// @brief Default Destructor
        ~Position() = default;
    };
} // namespace ecs

#endif /* !POSITIONCOMPONENT_HPP_ */
