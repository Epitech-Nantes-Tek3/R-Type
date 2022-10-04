/*
** EPITECH PROJECT, 2022
** Project
** File description:
** LifeComponent
*/

#ifndef LIFECOMPONENT_HPP_
#define LIFECOMPONENT_HPP_

#include "Component.hpp"

namespace ecs
{
    /// @brief The Life class, needed for every ennemies, bosses or players
    class Life : public Component{
      public:
        /// @brief The life's point of the entity at the beginning
        unsigned short lifePoint;

        /// @brief Constructor of the Life Component
        /// @param newLifePoint the life given to the entity
        Life(unsigned short newLifePoint) : lifePoint(newLifePoint) {};
        /// @brief Copy Constructor of the Life component
        /// @param old The copy of the Life component
        Life(const Life &old) : lifePoint(old.lifePoint) {};
        /// @brief Default Destructor
        ~Life() = default;
    };
} // namespace ecs

#endif /* !LIFECOMPONENT_HPP_ */
