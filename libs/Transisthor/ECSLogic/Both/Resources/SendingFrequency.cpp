/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** SendingFrequency
*/

#include "SendingFrequency.hpp"

using namespace transisthor::ecslogic;

SendingFrequency::SendingFrequency()
{
    _frequency = std::chrono::duration<double>(0.3);
    _lastTimeNew = std::chrono::steady_clock::now();
    _lastTimeUpdate = std::chrono::steady_clock::now();
}

bool SendingFrequency::canBeRunNew()
{
    return (std::chrono::steady_clock::now() - _lastTimeUpdate > _frequency);
}

bool SendingFrequency::canBeRunUpdate()
{
    return (std::chrono::steady_clock::now() - _lastTimeUpdate > _frequency);
}

void SendingFrequency::resetNewClock()
{
    _lastTimeNew = std::chrono::steady_clock::now();
}

void SendingFrequency::resetUpdateClock()
{
    _lastTimeUpdate = std::chrono::steady_clock::now();
}
