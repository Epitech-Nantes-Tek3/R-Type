/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** CreateEnemy
*/

#ifndef CREATEENEMY_HPP_
#define CREATEENEMY_HPP_

#include "GameComponents/CollidableComponent.hpp"
#include "GameComponents/DamageComponent.hpp"
#include "GameComponents/DamageRadiusComponent.hpp"
#include "GameComponents/EnemyComponent.hpp"
#include "GameComponents/LifeComponent.hpp"
#include "GameComponents/LifeTimeComponent.hpp"
#include "GameComponents/NewlyCreated.hpp"
#include "GameComponents/PositionComponent.hpp"
#include "GameComponents/SizeComponent.hpp"
#include "GameComponents/VelocityComponent.hpp"
#include "GameComponents/WeightComponent.hpp"
#include "GameComponents/DestinationComponent.hpp"
#include "GameSharedResources/Random.hpp"
#include "Transisthor/TransisthorECSLogic/Both/Components/Networkable.hpp"
#include "World/World.hpp"
#include "SFMLComponents/LayerLvL.hpp"

#define MINIMUM_WIDTH  1400
#define MAXIMUM_WIDTH  1920
#define MINIMUM_HEIGTH 0
#define MAXIMUM_HEIGTH 1080

namespace ecs
{
    /// @brief This function creates a new Enemy Entity with these parameters
    /// @param world The world in which the Enemy must be created
    /// @param posX Position x of the Enemy
    /// @param posY Position y of the Enemy
    /// @param multiplierAbscissa The Velocity multiplierAbscissa for the new Enemy
    /// @param multiplierOrdinate The Velocity multiplierOrdinate for the new Enemy
    /// @param weight Weight of the Enemy
    /// @param sizeX Size x of the Enemy
    /// @param sizeY Size y of the Enemy
    /// @param life Life of the Enemy
    /// @param damage Damage of projectiles fired by this Enemy
    /// @param damageRadius DamageRadius of projectiles fired by this Enemy
    /// @param uuid The uuid of the entity. Can be empty.
    /// @param networkId The id of the Networkable Component. In the client instance, it MUST NOT be filled in.
    /// @return Id of the new Enemy in std::size_t
    inline std::size_t createNewEnemy(World &world, const int posX, const int posY, const double multiplierAbscissa,
        const double multiplierOrdinate, const short weight, const int sizeX, const int sizeY,
        const unsigned short life, const unsigned short damage, const unsigned short damageRadius,
        const std::string uuid = "", const unsigned short networkId = 0)
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
                             .addComponent<Velocity>(multiplierAbscissa, multiplierOrdinate)
                             .addComponent<Enemy>();

        if (networkId) {
            // Case : Creation in a server instance
            entity.addComponent<NewlyCreated>(uuid, false);
            entity.addComponent<Networkable>(networkId);
            entity.addComponent<Destination>(world.getResource<RandomDevice>().randInt(MINIMUM_WIDTH, MAXIMUM_WIDTH), world.getResource<RandomDevice>().randInt(MINIMUM_HEIGTH, MAXIMUM_HEIGTH));
        } else {
            // Case : Creation in a Client instance
            if (uuid != "") {
                // Special case : the client created the entity and not the server
                entity.addComponent<NewlyCreated>(uuid, true);
            }
            entity.addComponent<LayerLvL>(LayerLvL::layer_e::ENEMY);
        }
        return entity.getId();
    }

    /// @brief This function creates a new Enemy Entity with random position and with these parameters
    /// @param world The world in which the Enemy must be created
    /// @param multiplierAbscissa The Velocity multiplierAbscissa for the new Enemy
    /// @param multiplierOrdinate The Velocity multiplierOrdinate for the new Enemy
    /// @param weight Weight of the Enemy
    /// @param sizeX Size x of the Enemy
    /// @param sizeY Size y of the Enemy
    /// @param life Life of the Enemy
    /// @param damage Damage of projectiles fired by this Enemy
    /// @param damageRadius DamageRadius of projectiles fired by this Enemy
    /// @param uuid The uuid of the entity. Can be empty.
    /// @param networkId The id of the Networkable Component. In the client instance, it MUST NOT be filled in.
    /// @return Id of the new Enemy in std::size_t
    inline std::size_t createNewEnemyRandom(World &world, const double multiplierAbscissa,
        const double multiplierOrdinate, const short weight, const int sizeX, const int sizeY,
        const unsigned short life, const unsigned short damage, const unsigned short damageRadius,
        const std::string uuid = "", const unsigned short networkId = 0)
    {
        return createNewEnemy(world, world.getResource<RandomDevice>().randInt(MINIMUM_WIDTH, MAXIMUM_WIDTH),
            world.getResource<RandomDevice>().randInt(MINIMUM_HEIGTH, MAXIMUM_HEIGTH), multiplierAbscissa,
            multiplierOrdinate, weight, sizeX, sizeY, life, damage, damageRadius, uuid, networkId);
    }

} // namespace ecs
#endif /* !CREATEENEMY_HPP_ */
