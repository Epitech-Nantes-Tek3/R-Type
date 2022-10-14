/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** PositionComponent
*/

#ifndef POSITIONCOMPONENT_HPP_
#define POSITIONCOMPONENT_HPP_

#include "Component/Component.hpp"

namespace ecs
{
    /// @brief The Position component, almost used for every entities
    /// It's a networkable component.
    class Position : public Component {
      public:
        /// @brief The abscissa of the Position
        double x;
        /// @brief The ordinate of the Position
        double y;
        /// @brief The network status of the component. True if it has been modified since it was last sent.
        bool modified;

        /// @brief Constructor of the Position component
        /// @param X the abscissa
        /// @param Y the ordinate
        Position(const int &X = 0, const int &Y = 0) : x(X), y(Y), modified(false){};
        /// @brief Default Destructor
        ~Position() = default;
    };
} // namespace ecs

#endif /* !POSITIONCOMPONENT_HPP_ */
