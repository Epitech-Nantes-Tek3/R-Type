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

namespace rtypelogic::global
{
    /// @brief The LifeTime class, telling how long an entity is going to live
    class LifeTime : public ecs::Component {
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
} // namespace rtypelogic::global

#endif /* !LIFETIMECOMPONENT_HPP_ */
