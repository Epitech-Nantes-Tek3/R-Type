/*
** EPITECH PROJECT, 2022
** Project
** File description:
** DestinationComponent
*/

#ifndef DESTINATIONCOMPONENT_HPP_
#define DESTINATIONCOMPONENT_HPP_

#include "Component/Component.hpp"

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
        Destination(const int &X = 0, const int &Y = 0) : x(X), y(Y){};
        /// @brief Default Destructor
        ~Destination() = default;
    };
} // namespace ecs

#endif /* !DirectionCOMPONENT_HPP_ */
