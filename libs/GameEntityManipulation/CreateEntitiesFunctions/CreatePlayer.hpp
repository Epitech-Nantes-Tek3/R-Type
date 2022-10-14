/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** CreatePlayer
*/

#ifndef CREATEPLAYER_HPP_
#define CREATEPLAYER_HPP_

#include "GameComponents/CollidableComponent.hpp"
#include "GameComponents/DamageComponent.hpp"
#include "GameComponents/DamageRadiusComponent.hpp"
#include "GameComponents/LifeComponent.hpp"
#include "GameComponents/LifeTimeComponent.hpp"
#include "GameComponents/NewlyCreated.hpp"
#include "GameComponents/PlayerComponent.hpp"
#include "GameComponents/PositionComponent.hpp"
#include "GameComponents/SizeComponent.hpp"
#include "GameComponents/VelocityComponent.hpp"
#include "GameComponents/WeightComponent.hpp"
#include "GameSharedResources/Random.hpp"
#include "Transisthor/TransisthorECSLogic/Both/Components/Networkable.hpp"
#include "World/World.hpp"

namespace ecs
{
    /// @brief This function creates a new Player Entity with these parameters
    /// @param world The world in which the Player must be created
    /// @param posX Position x of the Player
    /// @param posY Position y of the Player
    /// @param weight Weight of the Player
    /// @param size_x Size x of the player
    /// @param size_y Size y of the player
    /// @param multiplierAbscissa The Velocity multiplierAbscissa for the new Player
    /// @param multiplierOrdinate The Velocity multiplierOrdinate for the new Player
    /// @param life Life of the Player
    /// @param damage Damage of projectiles fired by this Player
    /// @param damageRadius DamageRadius of projectiles fired by this Player
    /// @param uuid The uuid of the entity. Can be empty.
    /// @param networkId The id of the Networkable Component. In the client instance, it MUST NOT be filled in.
    /// @return Id of the new Player in std::size_t
    inline std::size_t createNewPlayer(World &world, const int posX, const int posY, const double multiplierAbscissa,
        const double multiplierOrdinate, const short weight, const int size_x, const int size_y,
        const unsigned short life, const unsigned short damage, const unsigned short damageRadius,
        const std::string uuid = "", unsigned short networkId = 0)
    {
        Entity &entity = world.addEntity()
                             .addComponent<Position>(posX, posY)
                             .addComponent<Weight>(weight)
                             .addComponent<Size>(size_x, size_y)
                             .addComponent<LifeTime>()
                             .addComponent<Life>(life)
                             .addComponent<Damage>(damage)
                             .addComponent<DamageRadius>(damageRadius)
                             .addComponent<Collidable>()
                             .addComponent<Velocity>(multiplierAbscissa, multiplierOrdinate)
                             .addComponent<Player>();
        if (networkId) {
            // Case : Creation in a server instance
            entity.addComponent<NewlyCreated>(uuid, false);
            entity.addComponent<Networkable>(networkId);
        } else {
            // Case : Creation in a Client instance
            if (uuid != "") {
                // Special case : the client created the entity and not the server
                entity.addComponent<NewlyCreated>(uuid, true);
            }
        }
        return entity.getId();
    }

} // namespace ecs
#endif /* !CREATEPLAYER_HPP_ */
