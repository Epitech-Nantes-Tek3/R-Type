/*
** EPITECH PROJECT, 2022
** Project
** File description:
** UpdateClockSystem
*/

#include "UpdateClockSystem.hpp"
#include <chrono>
#include <mutex>
#include "AnimationDelayComponent.hpp"
#include "R-TypeLogic/Global/Components/ShootingFrequencyComponent.hpp"
#include "R-TypeLogic/Server/Components/AfkFrequencyComponent.hpp"

using namespace ecs;

void UpdateClock::run(World &world)
{
    GameClock &clock = world.getResource<GameClock>();
    auto guard = std::lock_guard(clock);
    std::vector<std::shared_ptr<ecs::Entity>> joinedShoot = world.joinEntities<ShootingFrequency>();
    std::vector<std::shared_ptr<ecs::Entity>> joinedAfk = world.joinEntities<AfkFrequency>();
    std::vector<std::shared_ptr<ecs::Entity>> joinedAnimation =
        world.joinEntities<graphicECS::SFML::Components::AnimationDelayComponent>();

    clock.resetClock();
    for (auto it : joinedShoot)
        updateAFrequencyComponent<ShootingFrequency>(clock, it);
    for (auto it : joinedAfk)
        updateAFrequencyComponent<AfkFrequency>(clock, it);
    for (auto it : joinedAnimation)
        updateAFrequencyComponent<graphicECS::SFML::Components::AnimationDelayComponent>(clock, it);
}
