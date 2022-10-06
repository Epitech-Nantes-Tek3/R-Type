/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** LifetimeComponent
*/

#ifndef LIFETIMECOMPONENT_HPP_
#define LIFETIMECOMPONENT_HPP_

#include "Component/Component.hpp"
#include <chrono>

using namespace std::chrono;

namespace ecs
{
    /// @brief The Lifetime class, telling how long an entity is going to live
    class Lifetime : public Component{
      public:
        /// @brief the life time of the entity
        duration<double> timeLeft;

        /// @brief Constructor of the Lifetime
        /// @param newLifetime the life time of the entity
        Lifetime(const duration<double> &newLifetime = duration<double>(0)) : timeLeft(newLifetime) {};
        /// @brief Default destructor
        ~Lifetime() = default;

    };
} // namespace ecs

#endif /* !LIFETIMECOMPONENT_HPP_ */
