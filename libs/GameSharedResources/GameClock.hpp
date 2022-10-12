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
    class GameClock : public Resource {
    public:

        GameClock();

        ~GameClock();

        double elapsedTime();
    private:
        std::chrono::steady_clock::time_point _lastReset;
};
} // namespace ecs

#endif /* !GAMECLOCK_HPP_ */
