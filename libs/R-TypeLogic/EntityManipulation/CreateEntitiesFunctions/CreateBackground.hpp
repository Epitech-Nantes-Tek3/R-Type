/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** CreateBackground
*/

#ifndef CREATEBACKGROUND_HPP_
#define CREATEBACKGROUND_HPP_

#include "World/World.hpp"
#include "R-TypeLogic/Components/BackGroundComponent.hpp"
#include "R-TypeLogic/Components/CollidableComponent.hpp"
#include "R-TypeLogic/Components/DamageComponent.hpp"
#include "R-TypeLogic/Components/PositionComponent.hpp"
#include "R-TypeLogic/Components/SizeComponent.hpp"
#include "R-TypeLogic/Components/VelocityComponent.hpp"
#include "R-TypeLogic/Components/WeightComponent.hpp"

namespace ecs
{
    /// @brief This function creates a new BackGround Entity with these parameters
    /// @param world The world in which the BackGround must be created
    /// @param posX Position x of the BackGround
    /// @param posY Position y of the BackGround
    /// @param weight Weight of the BackGround
    /// @param sizeX Size x of the player
    /// @param sizeY Size y of the player
    /// @param multiplierAbscissa The Velocity multiplierAbscissa for the new BackGround
    /// @param multiplierOrdinate The Velocity multiplierOrdinate for the new BackGround
    /// @return Id of the new BackGround in std::size_t
    inline std::size_t createNewBackGround(World &world, const int posX, const int posY,
        const double multiplierAbscissa, const double multiplierOrdinate, const short weight, const int sizeX,
        const int sizeY)
    {
        return world.addEntity()
            .addComponent<Position>(posX, posY)
            .addComponent<Weight>(weight)
            .addComponent<Size>(sizeX, sizeY)
            .addComponent<Collidable>()
            .addComponent<Velocity>(multiplierAbscissa, multiplierOrdinate)
            .addComponent<BackGround>()
            .getId();
    }

} // namespace ecs

#endif /* !CREATEBACKGROUND_HPP_ */
