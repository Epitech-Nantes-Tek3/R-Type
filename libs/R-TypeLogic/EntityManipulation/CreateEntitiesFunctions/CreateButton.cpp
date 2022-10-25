/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** CreateButton
*/

#include "CreateButton.hpp"

namespace ecs
{
    std::size_t createNewButton(World &world, const int posX, const int posY, const int sizeX, const int sizeY)
    {
        return world.addEntity()
            .addComponent<Position>(posX, posY)
            .addComponent<Size>(sizeX, sizeY)
            .addComponent<Button>()
            .getId();
    }
} // namespace ecs