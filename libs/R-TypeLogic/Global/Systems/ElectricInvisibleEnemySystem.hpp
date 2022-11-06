/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** ElectricInvisibleEnemy
*/

#ifndef ELECTRICINVISIBLEENEMY_HPP_
#define ELECTRICINVISIBLEENEMY_HPP_

#include "World/World.hpp"
#include "R-TypeLogic/Global/Components/InvisibleComponent.hpp"

namespace ecs
{
    /// @brief This is the Electric Invisible System. It makes the electric enemy invisible
    /// if they are not in range of 100 of their destination
    struct ElectricInvisibleEnemy : public System {
        /// @brief Run the ElectricInvisibleEnemy system
        /// @param world the world where the electric enemies are
        void run(World &world) override final;
    };

} // namespace ecs

#endif /* !ELECTRICINVISIBLEENEMY_HPP_ */
