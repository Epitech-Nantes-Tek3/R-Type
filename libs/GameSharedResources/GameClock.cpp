/*
** EPITECH PROJECT, 2022
** Project
** File description:
** GameClock
*/

#include "GameClock.hpp"

using namespace std::chrono;
using namespace ecs;

GameClock::GameClock() : _lastTime(steady_clock::now()) {}

double GameClock::getElapsedTime()
{
    duration<double> elapsedTime = steady_clock::now() - this->_lastTime;

    return elapsedTime.count();
}

void GameClock::resetClock() { this->_lastTime = std::chrono::steady_clock::now(); };