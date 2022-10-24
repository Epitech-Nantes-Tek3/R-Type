/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** CreateButton
*/

#include "CreateButton.hpp"

namespace ecs
{
    std::size_t createNewButton(World &world, const int posX, const int posY, const double multiplierAbscissa,
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