/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** CreateBackground
*/

#include "CreateBackground.hpp"

namespace ecs
{
    std::size_t createNewBackGround(World &world, const int posX, const int posY, const double multiplierAbscissa,
        const double multiplierOrdinate, const short weight, const int sizeX, const int sizeY)
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