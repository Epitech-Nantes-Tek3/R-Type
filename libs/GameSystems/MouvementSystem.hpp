/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** Mouvement
*/

#ifndef MOUVEMENT_HPP_
#define MOUVEMENT_HPP_

#include <World/World.hpp>
#include <GameComponents/PositionComponent.hpp>
#include <GameComponents/VelocityComponent.hpp>
#include <algorithm>
#include <iostream>

using namespace ecs;

struct Movement : public ecs::System {
    void run(ecs::World &world) override final
    {
        std::vector<std::shared_ptr<ecs::Entity>> joined = world.joinEntities<Position, Velocity>();


        auto move = [](std::shared_ptr<ecs::Entity> entityPtr) {
            Position &pos = entityPtr.get()->getComponent<Position>();
            Velocity &vel = entityPtr.get()->getComponent<Velocity>();

            pos.x += vel.multiplierAbscissa;
            pos.y += vel.multiplierOrdinate;
        };
        std::for_each(joined.begin(), joined.end(), move);
    }
};

#endif /* !MOUVEMENT_HPP_ */
