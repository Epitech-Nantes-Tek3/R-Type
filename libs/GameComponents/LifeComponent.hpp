/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** LifeComponent
*/

#ifndef LIFECOMPONENT_HPP_
#define LIFECOMPONENT_HPP_

#include "Component/Component.hpp"

namespace ecs
{
    /// @brief The Life class, needed for every ennemies, bosses or players
    /// It's a networkable component.
    class Life : public Component {
      public:
        /// @brief The life's point of the entity at the beginning
        unsigned short lifePoint;
        /// @brief The network status of the component. True if it has been modified since it was last sent.
        bool modified;

        /// @brief If the server need to resend it to everyone
        bool sendToEveryone;

        /// @brief Constructor of the Life Component
        /// @param newLifePoint the life given to the entity
        Life(unsigned short newLifePoint = 0) : lifePoint(newLifePoint), modified(false), sendToEveryone(false){};
        /// @brief Default Destructor
        ~Life() = default;
    };
} // namespace ecs

#endif /* !LIFECOMPONENT_HPP_ */
