/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** CreateBackground
*/

#ifndef CREATEBACKGROUND_HPP_
#define CREATEBACKGROUND_HPP_

#include "GameComponents/CollidableComponent.hpp"
#include "GameComponents/DamageComponent.hpp"
#include "GameComponents/BackGroundComponent.hpp"
#include "GameComponents/PositionComponent.hpp"
#include "GameComponents/SizeComponent.hpp"
#include "GameComponents/VelocityComponent.hpp"
#include "GameComponents/WeightComponent.hpp"
#include "World/World.hpp"

namespace ecs
{
    /// @brief This function creates a new BackGround Entity with these parameters
    /// @param world The world in which the BackGround must be created
    /// @param pos_x Position x of the BackGround
    /// @param pos_y Position y of the BackGround
    /// @param weight Weight of the BackGround
    /// @param size_x Size x of the player
    /// @param size_y Size y of the player
    /// @param multiplierAbscissa The Velocity multiplierAbscissa for the new BackGround
    /// @param multiplierOrdinate The Velocity multiplierOrdinate for the new BackGround
    /// @return Id of the new BackGround in std::size_t
    inline std::size_t createNewBackGround(World &world, const int pos_x, const int pos_y, const double multiplierAbscissa,
        const double multiplierOrdinate, const short weight, const int size_x, const int size_y)
    {
        return world.addEntity()
            .addComponent<Position>(pos_x, pos_y)
            .addComponent<Weight>(weight)
            .addComponent<Size>(size_x, size_y)
            .addComponent<Collidable>()
            .addComponent<Velocity>(multiplierAbscissa, multiplierOrdinate)
            .addComponent<BackGround>()
            .getId();
    }

} // namespace ecs

#endif /* !CREATEBACKGROUND_HPP_ */
