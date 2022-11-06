/*
** EPITECH PROJECT, 2022
** Project
** File description:
** ElectricInvisibleEnemy
*/

#include "ElectricInvisibleEnemySystem.hpp"
#include "R-TypeLogic/Global/Components/InvisibleComponent.hpp"
#include "R-TypeLogic/Global/Components/EnemyComponent.hpp"
#include "R-TypeLogic/Global/Components/PositionComponent.hpp"
#include "R-TypeLogic/Global/Components/DestinationComponent.hpp"

using namespace ecs;

void ElectricInvisibleEnemy::run(World &world)
{
    std::vector<std::shared_ptr<ecs::Entity>> joined = world.joinEntities<Enemy, Destination, Position>();

    auto makeInvisibleElectricEnemy = [] (std::shared_ptr<Entity> entityPtr) {
        auto guard = std::lock_guard(*entityPtr.get());

        if (entityPtr->getComponent<Enemy>().enemyType != Enemy::ELECTRIC)
            return;

        Position &pos = entityPtr.get()->getComponent<Position>();
        Destination &dest = entityPtr.get()->getComponent<Destination>();

        if (pos.x - 300 <= dest.x && dest.x <= pos.x + 300 && pos.y - 300 <= dest.y && dest.y <= pos.y + 300) {
            if (!entityPtr->contains<Invisible>()) {
                entityPtr->addComponent<Invisible>();
            }
        }
        else if (entityPtr->contains<Invisible>()) {
            entityPtr->removeComponent<Invisible>();
        }

    };
    std::for_each(joined.begin(), joined.end(), makeInvisibleElectricEnemy);
}