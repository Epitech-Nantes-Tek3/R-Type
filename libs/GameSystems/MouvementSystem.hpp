/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** Mouvement
*/

#ifndef MOUVEMENT_HPP_
#define MOUVEMENT_HPP_

#include "World/World.hpp"

namespace ecs
{
    /// @brief This is the Movement system. This system can move any entities which contains a Position and a Velocity
    /// Components It's a system that will be called by the engine world with the function runSystem()
    struct Movement : public System {
        void run(World &world) override final;
        // {
        //     std::vector<std::shared_ptr<ecs::Entity>> joined = world.joinEntities<Position, Velocity>();
        //     GameClock &clock = world.getResource<GameClock>();
        //     double elapsedTimeInSeconds = clock.elapsedTime();

        //     auto move = [&elapsedTimeInSeconds](std::shared_ptr<ecs::Entity> entityPtr) {
        //         Position &pos = entityPtr.get()->getComponent<Position>();
        //         Velocity &vel = entityPtr.get()->getComponent<Velocity>();

        //         pos.x += (vel.multiplierAbscissa * elapsedTimeInSeconds);
        //         pos.y += (vel.multiplierOrdinate * elapsedTimeInSeconds);
        //     };
        //     std::for_each(joined.begin(), joined.end(), move);
        // }
    };
} // namespace ecs

#endif /* !MOUVEMENT_HPP_ */
