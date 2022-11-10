/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** GlobalScore
*/

#include "GlobalScore.hpp"
#include "R-TypeLogic/Global/Components/EnemyComponent.hpp"

using namespace ecs;

void GlobalScore::updateScore(unsigned int enemyType)
{
    switch (enemyType) {
        case Enemy::FIRE : _score += 3; break;
        case Enemy::ICE : _score += 5; break;
        case Enemy::ELECTRIC : _score += 10; break;
        case Enemy::BOSS : _score += 50; break;
        default : _score += 1; break;
    }
}