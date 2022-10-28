/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** CreateBackground
*/

#include <boost/asio/thread_pool.hpp>
#include "CreateBackground.hpp"

namespace ecs
{
    std::size_t createNewBackGround(World &world, const int posX, const int posY, const double multiplierAbscissa,
        const double multiplierOrdinate, const short weight, const int sizeX, const int sizeY)
    {
        Entity &entity = world.addEntity();
        auto guard = std::lock_guard(entity);
        entity.addComponent<Position>(posX, posY)
            .addComponent<Weight>(weight)
            .addComponent<Size>(sizeX, sizeY)
            .addComponent<Collidable>()
            .addComponent<Velocity>(multiplierAbscissa, multiplierOrdinate)
            .addComponent<BackGround>();
        return entity.getId();
    }
} // namespace ecs
