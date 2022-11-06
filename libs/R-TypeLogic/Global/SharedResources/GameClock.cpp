/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** GameClock
*/

#include "GameClock.hpp"

using namespace std::chrono;
using namespace ecs;

GameClock::GameClock() : _lastResetTime(steady_clock::now()), _lastElapsedTime(0) {}

double GameClock::getElapsedTime()
{
    return _lastElapsedTime;
}

void GameClock::resetClock()
{
    std::chrono::duration<double> tmp = steady_clock::now() - _lastResetTime;
    _lastElapsedTime = tmp.count();
    _lastResetTime = std::chrono::steady_clock::now();
};