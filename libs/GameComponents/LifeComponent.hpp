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
    class Life : public Component{
      public:
        /// @brief The life's point of the entity at the beginning
        unsigned short lifePoint;

        /// @brief Constructor of the Life Component
        /// @param newLifePoint the life given to the entity
        Life(unsigned short newLifePoint = 0) : lifePoint(newLifePoint) {};
        /// @brief Default Destructor
        ~Life() = default;
    };
} // namespace ecs

#endif /* !LIFECOMPONENT_HPP_ */
