/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** UpdateClockSystem
*/

#ifndef UPDATECLOCKSYSTEM_HPP_
#define UPDATECLOCKSYSTEM_HPP_

#include <chrono>
#include "World/World.hpp"
#include "R-TypeLogic/Global/SharedResources/GameClock.hpp"

namespace ecs
{
    /// @brief UpdateClock System. Will be used to call the GameClock's reset
    struct UpdateClock : public System {
        /// @brief Run the UpdateClock System
        /// @param world The world where the clock will run
        void run(World &world) override final;

        /// @brief Change the time of a frequency component.
        /// @tparam C Type of the frequency component
        /// @param clock The world game clock
        /// @param entityPtr Entity attached to the frequency
        template <std::derived_from<ecs::Component> C>
        void updateAFrequencyComponent(GameClock &clock, std::shared_ptr<ecs::Entity> entityPtr)
        {
            C &freq = entityPtr.get()->getComponent<C>();
            double delta = freq.frequency.count() - clock.getElapsedTime();

            if (delta <= 0.0) {
                freq.frequency = std::chrono::duration<double>(0);
                return;
            }
            freq.frequency = std::chrono::duration<double>(delta);
        }
    };
}; // namespace ecs

#endif /* !UPDATECLOCKSYSTEM_HPP_ */
