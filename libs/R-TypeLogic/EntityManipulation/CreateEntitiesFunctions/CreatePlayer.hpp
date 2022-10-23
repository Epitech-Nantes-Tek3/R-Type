/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** CreatePlayer
*/

#ifndef CREATEPLAYER_HPP_
#define CREATEPLAYER_HPP_

#include "Transisthor/ECSLogic/Both/Components/Networkable.hpp"
#include "World/World.hpp"
#include "R-TypeLogic/Global/Components/CollidableComponent.hpp"
#include "R-TypeLogic/Global/Components/ControlableComponent.hpp"
#include "R-TypeLogic/Global/Components/DamageComponent.hpp"
#include "R-TypeLogic/Global/Components/DamageRadiusComponent.hpp"
#include "R-TypeLogic/Global/Components/LayerLvL.hpp"
#include "R-TypeLogic/Global/Components/LifeComponent.hpp"
#include "R-TypeLogic/Global/Components/LifeTimeComponent.hpp"
#include "R-TypeLogic/Global/Components/NewlyCreated.hpp"
#include "R-TypeLogic/Global/Components/PlayerComponent.hpp"
#include "R-TypeLogic/Global/Components/PositionComponent.hpp"
#include "R-TypeLogic/Global/Components/ShootingFrequencyComponent.hpp"
#include "R-TypeLogic/Global/Components/SizeComponent.hpp"
#include "R-TypeLogic/Global/Components/VelocityComponent.hpp"
#include "R-TypeLogic/Global/Components/WeightComponent.hpp"
#include "R-TypeLogic/Global/SharedResources/Random.hpp"

using namespace rtypelogic::global;
using namespace transisthor::ecslogic;
using namespace ecs;

namespace rtypelogic::entitymanipulation
{
    /// @brief This function creates a new Player Entity with these parameters
    /// @param world The world in which the Player must be created
    /// @param posX Position x of the Player
    /// @param posY Position y of the Player
    /// @param weight Weight of the Player
    /// @param sizeX Size x of the player
    /// @param sizeY Size y of the player
    /// @param multiplierAbscissa The Velocity multiplierAbscissa for the new Player
    /// @param multiplierOrdinate The Velocity multiplierOrdinate for the new Player
    /// @param life Life of the Player
    /// @param damage Damage of projectiles fired by this Player
    /// @param damageRadius DamageRadius of projectiles fired by this Player
    /// @param uuid The uuid of the entity. Can be empty.
    /// @param networkId The id of the Networkable Component. In the client instance, it MUST NOT be filled in.
    /// @return Id of the new Player in std::size_t
    inline std::size_t createNewPlayer(World &world, const int posX, const int posY, const double multiplierAbscissa,
        const double multiplierOrdinate, const short weight, const int sizeX, const int sizeY,
        const unsigned short life, const unsigned short damage, const unsigned short damageRadius, bool controlable,
        const std::string uuid = "", unsigned short networkId = 0)
    {
        Entity &entity = world.addEntity()
                             .addComponent<Position>(posX, posY)
                             .addComponent<Weight>(weight)
                             .addComponent<Size>(sizeX, sizeY)
                             .addComponent<LifeTime>()
                             .addComponent<Life>(life)
                             .addComponent<Damage>(damage)
                             .addComponent<DamageRadius>(damageRadius)
                             .addComponent<Collidable>()
                             .addComponent<ShootingFrequency>(0.05)
                             .addComponent<Velocity>(multiplierAbscissa, multiplierOrdinate)
                             .addComponent<Player>();
        if (controlable == true) {
            entity.addComponent<Controlable>();
        }
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
            entity.addComponent<LayerLvL>(LayerLvL::layer_e::PLAYER);
        }
        return entity.getId();
    }

} // namespace ecs
#endif /* !CREATEPLAYER_HPP_ */
