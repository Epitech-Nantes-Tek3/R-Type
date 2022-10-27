/*
** EPITECH PROJECT, 2022
** Project
** File description:
** UpdateClockSystem
*/

#include "UpdateClockSystem.hpp"
#include <chrono>
#include "R-TypeLogic/Global/SharedResources/GameClock.hpp"
#include "R-TypeLogic/Global/Components/ShootingFrequencyComponent.hpp"

using namespace ecs;

void UpdateClock::run(World &world)
{
    GameClock &clock = world.getResource<GameClock>();
    std::vector<std::shared_ptr<ecs::Entity>> joined = world.joinEntities<ShootingFrequency>();

    auto updateShootingFrequency = [&world, &clock](std::shared_ptr<ecs::Entity> entityPtr) {
        ShootingFrequency &freq = entityPtr.get()->getComponent<ShootingFrequency>();
        double delta = freq.frequency.count() - clock.getElapsedTime();

        if (delta <= 0.0) {
            freq.frequency = duration<double>(0);
            return;
        }
        freq.frequency = duration<double>(delta);
    };

    clock.resetClock();
    std::for_each(joined.begin(), joined.end(), updateShootingFrequency);
}
