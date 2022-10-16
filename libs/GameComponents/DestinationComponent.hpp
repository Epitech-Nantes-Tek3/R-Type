/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** DestinationComponent
*/

#ifndef DESTINATIONCOMPONENT_HPP_
#define DESTINATIONCOMPONENT_HPP_

#include "Component/Component.hpp"

namespace ecs
{
    /// @brief The Destination component, used for mobiles entities
    /// It's a networkable component.
    class Destination : public Component {
      public:
        /// @brief The abscissa of the Destination
        int x;
        /// @brief The ordinate of the Destination
        int y;
        /// @brief The network status of the component. True if it has been modified since it was last sent.
        bool modified;

        /// @brief If the server need to resend it to everyone
        bool sendToEveryone;

        /// @brief Constructor of the Destination component
        /// @param X the abscissa
        /// @param Y the ordinate
        Destination(const int &X = 0, const int &Y = 0) : x(X), y(Y), modified(false), sendToEveryone(false){};
        /// @brief Default Destructor
        ~Destination() = default;
    };
} // namespace ecs

#endif /* !DirectionCOMPONENT_HPP_ */
