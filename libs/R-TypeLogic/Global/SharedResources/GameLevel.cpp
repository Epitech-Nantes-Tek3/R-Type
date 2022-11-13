/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** GameLevel
*/

#include "GameLevel.hpp"

using namespace ecs;

GameLevel::GameLevel() : _currLevel(GameLevel::LEVEL_ONE), _waveChanged(true), _hasLevelChanged(false), _nbkills(0) {};

void GameLevel::addNewKills(unsigned int newKills)
{
    this->_nbkills += newKills;
    if (_currLevel == LEVEL_FORTH && _nbkills >= LEVEL_INFINITE) {
        _currLevel = LEVEL_INFINITE;
        _hasLevelChanged = true;
        _waveChanged = true;
        _musicChanged = true;
    }
    if (_currLevel == LEVEL_THREE && _nbkills >= LEVEL_FORTH) {
        _currLevel = LEVEL_FORTH;
        _hasLevelChanged = true;
        _waveChanged = true;
        _musicChanged = true;
    }
    if (_currLevel == LEVEL_TWO && _nbkills >= LEVEL_THREE) {
        _currLevel = LEVEL_THREE;
        _hasLevelChanged = true;
        _waveChanged = true;
        _musicChanged = true;
    }
    if (_currLevel == LEVEL_ONE && _nbkills >= LEVEL_TWO) {
        _currLevel = LEVEL_TWO;
        _hasLevelChanged = true;
        _waveChanged = true;
        _musicChanged = true;
    }
}
