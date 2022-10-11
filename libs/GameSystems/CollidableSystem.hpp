/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** CollidableSystem
*/

#ifndef COLLIDABLESYSTEM_HPP_
#define COLLIDABLESYSTEM_HPP_

#include "World/World.hpp"

namespace ecs
{
    /// @brief This is the Collidable System.
    /// This system will check every entities, see if they collide and apply damage on consequence
    /// Needed Component : Collidable, Position, Size, Damage
    struct CollidableSystem : public System {
        inline void run(World &world) override final
        {
            
        }
    };
} // namespace ecs

#endif /* !COLLIDABLESYSTEM_HPP_ */
