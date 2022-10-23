/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** GameClock
*/

#ifndef GAMECLOCK_HPP_
#define GAMECLOCK_HPP_

#include <chrono>
#include "Resource/Resource.hpp"

namespace rtypelogic::global
{
    /// @brief Shared Resource Clock for the Game
    class GameClock : public ecs::Resource {
      public:
        /// @brief Create the Clock (Basic constructor)
        GameClock();

        /// @brief This function reinitialize the clock to the actual time
        void resetClock();

        /// @brief This function do the difference between now and the last time the clock was reset
        /// @return The difference between now and _lastTime
        double getElapsedTime();

      private:
        /// @brief The last time the clock was reset
        std::chrono::steady_clock::time_point _lastResetTime;

        /// @brief The Last elapsed time, to have the same elapsedTime for every system
        double _lastElapsedTime;
    };
} // namespace rtypelogic::global

#endif /* !GAMECLOCK_HPP_ */
