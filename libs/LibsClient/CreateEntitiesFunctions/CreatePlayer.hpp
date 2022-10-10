/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** CreatePlayer
*/

#ifndef CREATEPLAYER_HPP_
#define CREATEPLAYER_HPP_

#include "World/World.hpp"
#include "GameComponents/CollidableComponent.hpp"
#include "GameComponents/DamageComponent.hpp"
#include "GameComponents/DamageRadiusComponent.hpp"
#include "GameComponents/LifeComponent.hpp"
#include "GameComponents/LifeTimeComponent.hpp"
#include "GameComponents/PlayerComponent.hpp"
#include "GameComponents/PositionComponent.hpp"
#include "GameComponents/SizeComponent.hpp"
#include "GameComponents/VelocityComponent.hpp"
#include "GameComponents/WeightComponent.hpp"

namespace ecs
{
    /// @brief This function creates a new Player Entity with these parameters
    /// @param world The world in that the Player must be created
    /// @param pos_x Position x of the Player
    /// @param pos_y Position y of the Player
    /// @param weight Weight of the Player
    /// @param size_x Size x of the player
    /// @param size_y Size y of the player
    /// @param multiplierAbscissa The Velocity multiplierAbscissa for the new Player
    /// @param multiplierOrdinate The Velocity multiplierOrdinate for the new Player
    /// @param life Life of the Player
    /// @param damage Damage of projectiles fired by this Player
    /// @param damageRadius DamageRadius of projectiles fired by this Player
    /// @return Id of the new Player in std::size_t
    inline std::size_t createNewPlayer(World &world, const int pos_x, const int pos_y, const double multiplierAbscissa, const double multiplierOrdinate, const short weight, const int size_x, const int size_y, const unsigned short life, const unsigned short damage, const unsigned short damageRadius) {
                std::size_t new_player = world.addEntity()
                                     .addComponent<Position>(pos_x, pos_y)
                                     .addComponent<Weight>(weight)
                                     .addComponent<Size>(size_x, size_y)
                                     .addComponent<Lifetime>()
                                     .addComponent<Life>(life)
                                     .addComponent<Damage>(damage)
                                     .addComponent<DamageRadius>(damageRadius)
                                     .addComponent<Collidable>()
                                     .addComponent<Velocity>(multiplierAbscissa, multiplierOrdinate)
                                     .addComponent<Player>()
                                     .getId();
        return new_player;
    }

} // namespace ecs
#endif /* !CREATEPLAYER_HPP_ */
