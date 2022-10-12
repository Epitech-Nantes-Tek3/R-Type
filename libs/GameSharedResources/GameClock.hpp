/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** GameClock
*/

#ifndef GAMECLOCK_HPP_
#define GAMECLOCK_HPP_

#include "Resource/Resource.hpp"

#include <chrono>

namespace ecs
{
    /// @brief Shared Resource Clock for the Game
    class GameClock : public Resource {
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
        std::chrono::steady_clock::time_point _lastTime;
    };
} // namespace ecs

#endif /* !GAMECLOCK_HPP_ */
