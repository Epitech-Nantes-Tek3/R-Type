/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** GameLevel
*/

#include "GameLevel.hpp"

using namespace ecs;

void GameLevel::addNewKills(unsigned int newKills)
{
    this->_nbkills += newKills;
    if (_currLevel == LEVEL_FORTH && _nbkills >= INFINITE) {
        _currLevel = INFINITE;
        _hasLevelChanged = true;
    }
    if (_currLevel == LEVEL_THREE && _nbkills >= LEVEL_FORTH) {
        _currLevel = LEVEL_FORTH;
        _hasLevelChanged = true;
    }
    if (_currLevel == LEVEL_TWO && _nbkills >= LEVEL_THREE) {
        _currLevel = LEVEL_THREE;
        _hasLevelChanged = true;
    }
    if (_currLevel == LEVEL_ONE && _nbkills >= LEVEL_TWO) {
        _currLevel = LEVEL_TWO;
        _hasLevelChanged = true;
    }
}
