/*
** EPITECH PROJECT, 2022
** Project
** File description:
** DestinationComponent
*/

#ifndef DESTINATIONCOMPONENT_HPP_
#define DESTINATIONCOMPONENT_HPP_

#include "Component.hpp"

namespace ecs
{
    /// @brief The Destination component, used for mobiles entities
    class Destination : public Component {
      public:
        /// @brief The abscissa of the Destination
        int x;
        /// @brief The ordinate of the Destination
        int y;

        /// @brief Constructor of the Destination component
        /// @param X the abscissa
        /// @param Y the ordinate
        Destination(const int &X, const int &Y) : x(X), y(Y){};
        /// @brief Copy Constructor of the Destination Component
        /// @param old The copy of the Destination Component
        Destination(const Destination &old) : x(old.x), y(old.y) {};
        /// @brief Default Destructor
        ~Destination() = default;
    };
} // namespace ecs

#endif /* !DirectionCOMPONENT_HPP_ */
