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

        inline void resetClock() {this->_lastTime = std::chrono::steady_clock::now();};

        double elapsedTime();
    private:
        std::chrono::steady_clock::time_point _lastTime;
};
} // namespace ecs

#endif /* !GAMECLOCK_HPP_ */
