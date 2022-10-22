/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** CreatePlayer
*/

#ifndef CREATEPLAYER_HPP_
#define CREATEPLAYER_HPP_

#include "GameComponents/CollidableComponent.hpp"
#include "GameComponents/ControlableComponent.hpp"
#include "GameComponents/DamageComponent.hpp"
#include "GameComponents/DamageRadiusComponent.hpp"
#include "GameComponents/LayerLvL.hpp"
#include "GameComponents/LifeComponent.hpp"
#include "GameComponents/LifeTimeComponent.hpp"
#include "GameComponents/NewlyCreated.hpp"
#include "GameComponents/PlayerComponent.hpp"
#include "GameComponents/PositionComponent.hpp"
#include "GameComponents/ShootingFrequencyComponent.hpp"
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
    std::size_t createNewPlayer(World &world, const int posX, const int posY, const double multiplierAbscissa,
        const double multiplierOrdinate, const short weight, const int sizeX, const int sizeY,
        const unsigned short life, const unsigned short damage, const unsigned short damageRadius, bool controlable,
        const std::string uuid = "", unsigned short networkId = 0);

} // namespace ecs
#endif /* !CREATEPLAYER_HPP_ */
