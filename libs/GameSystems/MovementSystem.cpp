/*
** EPITECH PROJECT, 2022
** Project
** File description:
** MouvementSystem
*/

#include "MovementSystem.hpp"
#include "GameComponents/PositionComponent.hpp"
#include "GameComponents/VelocityComponent.hpp"
#include "GameComponents/PlayerComponent.hpp"
#include "GameComponents/EnemyComponent.hpp"
#include "GameComponents/DestinationComponent.hpp"
#include "GameSharedResources/GameClock.hpp"

using namespace ecs;

void Movement::run(World &world)
{
    std::vector<std::shared_ptr<ecs::Entity>> joined = world.joinEntities<Position, Velocity>();

    auto move = [&world](std::shared_ptr<ecs::Entity> entityPtr) {
        GameClock &clock = world.getResource<GameClock>();
        double elapsedTimeInSeconds = clock.getElapsedTime();
        Position &pos = entityPtr.get()->getComponent<Position>();
        Velocity &vel = entityPtr.get()->getComponent<Velocity>();
        //int change_dest_enemy = 0;
    
        if (vel.multiplierAbscissa == 0 && vel.multiplierOrdinate == 0)
            return;
        if (entityPtr->contains<Player>() == true) {
            if ((pos.x <= 4 && vel.multiplierAbscissa < 0))
                return;
            if ((pos.x >= 1912 && vel.multiplierAbscissa > 0))
                return;
            if ((pos.y <= 4 && vel.multiplierOrdinate < 0))
                return;
            if ((pos.y >= 1072 && vel.multiplierOrdinate > 0))
                return;
        }
        // Don't remove, it's for check if enemy arrived to the window border
        // if (entityPtr->contains<Enemy>() == true) {
        //     if ((pos.x <= 4 && vel.multiplierAbscissa < 0))
        //         change_dest_enemy++;
        //     if ((pos.x >= 1912 && vel.multiplierAbscissa > 0))
        //         change_dest_enemy++;
        //     if ((pos.y <= 4 && vel.multiplierOrdinate < 0))
        //         change_dest_enemy++;
        //     if ((pos.y >= 1072 && vel.multiplierOrdinate > 0))
        //         change_dest_enemy++;
        //     if (change_dest_enemy > 0) {
        //         entityPtr->getComponent<Destination>().x = pos.x;
        //         entityPtr->getComponent<Destination>().y = pos.y;
        //     }

        //}
        // pos.modified = true;

        pos.x += (vel.multiplierAbscissa * (((double((int)(elapsedTimeInSeconds * 100000000)))) / 100000000));
        pos.y += (vel.multiplierOrdinate * (((double((int)(elapsedTimeInSeconds * 100000000)))) / 100000000));
    };
    std::for_each(joined.begin(), joined.end(), move);
}
