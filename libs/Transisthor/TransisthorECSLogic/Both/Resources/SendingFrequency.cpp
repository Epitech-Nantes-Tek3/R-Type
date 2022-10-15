/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** SendingFrequency
*/

#include "SendingFrequency.hpp"

SendingFrequency::SendingFrequency()
{
    _frequency = std::chrono::duration<double>(0.3);
    _lastTimeNew = std::chrono::steady_clock::now();
    _lastTimeUpdate = std::chrono::steady_clock::now();
}

bool SendingFrequency::canBeRunNew()
{
    std::chrono::steady_clock::time_point now = std::chrono::steady_clock::now();
    if (now - this->_lastTimeNew > _frequency) {
        this->_lastTimeNew = now;
        return true;
    }
    return false;
}

bool SendingFrequency::canBeRunUpdate()
{
    std::chrono::steady_clock::time_point now = std::chrono::steady_clock::now();
    if (now - this->_lastTimeUpdate > _frequency) {
        this->_lastTimeUpdate = now;
        return true;
    }
    return false;
}
