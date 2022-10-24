/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** LifeTime
*/

#ifndef LIFETIMECOMPONENT_HPP_
#define LIFETIMECOMPONENT_HPP_

#include <chrono>
#include "Component/Component.hpp"

using namespace std::chrono;

namespace ecs
{
    /// @brief The LifeTime class, telling how long an entity is going to live
    class LifeTime : public Component {
      public:
        /// @brief the life time of the entity
        duration<double> timeLeft;

        /// @brief Constructor of the LifeTime
        /// @param newLifeTime the life time of the entity
        LifeTime(const duration<double> &newLifeTime) : timeLeft(newLifeTime){};

        /// @brief Constructor of the LifeTime
        /// @param newLifeTime the life time of the entity
        LifeTime(double newLifeTime = 0.0) : timeLeft(duration<double>(newLifeTime)){};
        /// @brief Default destructor
        ~LifeTime() = default;
    };
} // namespace ecs

#endif /* !LIFETIMECOMPONENT_HPP_ */
