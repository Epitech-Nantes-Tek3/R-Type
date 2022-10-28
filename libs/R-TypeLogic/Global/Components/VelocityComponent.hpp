/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** VelocityComponent
*/

#ifndef VELOCITYCOMPONENT_HPP_
#define VELOCITYCOMPONENT_HPP_

#include "Component/Component.hpp"

namespace ecs
{
    /// @brief The velocity class, multiplying the movement of the entity
    /// It's a networkable component.
    class Velocity : public Component {
      public:
        /// @brief The multiplier of the abscissa movement (between 0.1 and 10)
        double multiplierAbscissa;
        /// @brief The multiplier of the ordinate movement (between 0.1 and 10)
        double multiplierOrdinate;
        /// @brief The network status of the component. True if it has been modified since it was last sent.
        bool modified;
        /// @brief If the server need to resend it to everyone
        bool sendToEveryone;

        /// @brief Id of the client to delete from the Database after sending the death component. 0 if no client needed to be deleted
        unsigned short clientToDelete;

        /// @brief Constructor of the Velocity Component
        /// @param newMultiplierX the movement's multiplier of abscissa
        /// @param newMultiplierY the movement's multiplier of ordinate
        Velocity(double newMultiplierX = 0, double newMultiplierY = 0)
            : multiplierAbscissa(newMultiplierX), multiplierOrdinate(newMultiplierY), modified(false), sendToEveryone(false), clientToDelete(0){};
        /// @brief Default Destructor
        ~Velocity() = default;
    };
} // namespace ecs

#endif /* !VELOCITYCOMPONENT_HPP_ */
