/*
** EPITECH PROJECT, 2022
** Project
** File description:
** GameClock
*/

#include "GameClock.hpp"

using namespace std::chrono;

namespace ecs
{

    GameClock::GameClock() : _lastTime(steady_clock::now()) {}

    double GameClock::elapsedTime()
    {
        duration<double> elapsedTime = steady_clock::now() - this->_lastTime;

        return elapsedTime.count();
    }
} // namespace ecs
