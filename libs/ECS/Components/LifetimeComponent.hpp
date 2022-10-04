/*
** EPITECH PROJECT, 2022
** Project
** File description:
** LifetimeComponent
*/

#ifndef LIFETIMECOMPONENT_HPP_
#define LIFETIMECOMPONENT_HPP_

#include "Component.hpp"
#include <chrono>

using namespace std::chrono;

namespace ecs
{
    /// @brief The Lifetime class, telling how long an entity is going to live
    class Lifetime : public Component{
      public:
        /// @brief Store the current time, will be usefull in the corresponding system
        system_clock::time_point now = system_clock::now();
        /// @brief the life time of the entity
        duration<double> timeLeft;

        /// @brief Constructor of the Lifetime
        /// @param newLifetime the life time of the entity
        Lifetime(const duration<double> &newLifetime) : timeLeft(newLifetime) {};
        /// @brief Copy Constructor of the Lifetime Component
        /// @param old thecopy of the component
        Lifetime(const Lifetime &old) : timeLeft(old.timeLeft) {};
        /// @brief Default destructor
        ~Lifetime() = default;

    };
} // namespace ecs

#endif /* !LIFETIMECOMPONENT_HPP_ */
