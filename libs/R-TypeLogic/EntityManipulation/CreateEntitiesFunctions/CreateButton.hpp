/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** CreateButton
*/

#ifndef CREATEBUTTON_HPP_
#define CREATEBUTTON_HPP_

#include "World/World.hpp"
#include "R-TypeLogic/Components/ButtonComponent.hpp"
#include "R-TypeLogic/Components/CollidableComponent.hpp"
#include "R-TypeLogic/Components/DamageComponent.hpp"
#include "R-TypeLogic/Components/PositionComponent.hpp"
#include "R-TypeLogic/Components/SizeComponent.hpp"
#include "R-TypeLogic/Components/VelocityComponent.hpp"
#include "R-TypeLogic/Components/WeightComponent.hpp"

namespace ecs
{
    /// @brief This function creates a new Button Entity with these parameters
    /// @param world The world in which the Button must be created
    /// @param posX Position x of the Button
    /// @param posY Position y of the Button
    /// @param weight Weight of the Button
    /// @param sizeX Size x of the Button
    /// @param sizeY Size y of the Button
    /// @param multiplierAbscissa The Velocity multiplierAbscissa for the new Button
    /// @param multiplierOrdinate The Velocity multiplierOrdinate for the new Button
    /// @return Id of the new Button in std::size_t
    inline std::size_t createNewButton(World &world, const int posX, const int posY, const double multiplierAbscissa,
        const double multiplierOrdinate, const short weight, const int sizeX, const int sizeY)
    {
        return world.addEntity()
            .addComponent<Position>(posX, posY)
            .addComponent<Weight>(weight)
            .addComponent<Size>(sizeX, sizeY)
            .addComponent<Collidable>()
            .addComponent<Velocity>(multiplierAbscissa, multiplierOrdinate)
            .addComponent<Button>()
            .getId();
    }

} // namespace ecs

#endif /* !CREATEBUTTON_HPP_ */
