/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** CreateButton
*/

#ifndef CREATEBUTTON_HPP_
#define CREATEBUTTON_HPP_

#include "GameComponents/ButtonComponent.hpp"
#include "GameComponents/CollidableComponent.hpp"
#include "GameComponents/DamageComponent.hpp"
#include "GameComponents/PositionComponent.hpp"
#include "GameComponents/SizeComponent.hpp"
#include "GameComponents/VelocityComponent.hpp"
#include "GameComponents/WeightComponent.hpp"
#include "World/World.hpp"

namespace ecs
{
    /// @brief This function creates a new Button Entity with these parameters
    /// @param world The world in which the Button must be created
    /// @param posX Position x of the Button
    /// @param posY Position y of the Button
    /// @param weight Weight of the Button
    /// @param size_x Size x of the Button
    /// @param size_y Size y of the Button
    /// @param multiplierAbscissa The Velocity multiplierAbscissa for the new Button
    /// @param multiplierOrdinate The Velocity multiplierOrdinate for the new Button
    /// @return Id of the new Button in std::size_t
    inline std::size_t createNewButton(World &world, const int posX, const int posY, const double multiplierAbscissa,
        const double multiplierOrdinate, const short weight, const int size_x, const int size_y)
    {
        return world.addEntity()
            .addComponent<Position>(posX, posY)
            .addComponent<Weight>(weight)
            .addComponent<Size>(size_x, size_y)
            .addComponent<Collidable>()
            .addComponent<Velocity>(multiplierAbscissa, multiplierOrdinate)
            .addComponent<Button>()
            .getId();
    }

} // namespace ecs

#endif /* !CREATEBUTTON_HPP_ */
