/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** Transisthor
*/

/// @file libs/Transisthor/Transisthor.hpp

#ifndef TRANSISTHOR_HPP_
#define TRANSISTHOR_HPP_

#include "Communicator/Communicator.hpp"
#include "Error/Error.hpp"
#include "World/World.hpp"

using namespace ecs;
using namespace communicator_lib;

namespace communicator_lib
{
    class Communicator;
}

namespace transisthor_lib
{
    /// @brief Wrapper function to call sendDataToAClient in this file.
    /// @param communicator Instance of the communicator
    /// @param client Destination of the message
    /// @param data Content of the message
    /// @param size of the message
    /// @param type of the message
    void sendDataToAClientWithoutCommunicator(
        Communicator &communicator, Client &client, void *data, size_t size, unsigned short type);

    /// @brief Bridge between Communicator data and ECS data
    class Transisthor {
      public:
        /// @brief Construct a new Transisthor object
        /// @param communicator A reference to a working communicator
        /// @param ecsWorld A reference to a working ecs
        Transisthor(Communicator &communicator, World &ecsWorld);

        /// @brief Destroy a Transisthor object (Default value)
        ~Transisthor() = default;

        /// @brief Function called by the Communicator. The transfered data will be converted to an ECS object and send
        /// to the ecs.
        /// @param networkData Content of the network data (Refer to communicator lib document for more details)
        /// @return Return value his only used for testing (Unit and functional)
        void *transitNetworkDataToEcsDataComponent(Message networkData);

        /// @brief Function called by the Communicator. The transfered data will be converted to an ECS object and send
        /// to the ecs.
        /// @param networkData Content of the network data (Refer to communicator lib document for more details)
        /// @return Return value his only used for testing (Unit and functional)
        void *transitNetworkDataToEcsDataEntity(Message networkData);

        /// @brief Function called by the ECS. The transfered data will be converted to a Network object and send to the
        /// communicator.
        /// @tparam C Type of the component
        /// @param id Id of the transfered component
        /// @param type Type id of the component
        /// @param component The transfered component
        /// @param destination of the message
        /// @return Return value his only used for testing (Unit and functional)
        template <std::derived_from<Component> C>
        void *transitEcsDataToNetworkData(
            unsigned short id, unsigned short type, C component, std::vector<unsigned short> destination)
        {
            void *networkObject = std::malloc(((sizeof(C)) + sizeof(unsigned short) * 2));
            Client temporaryClient;

            if (networkObject == nullptr)
                throw error_lib::MallocError("Malloc failed.");
            std::memcpy(networkObject, &id, sizeof(unsigned short));
            std::memcpy((void *)((char *)networkObject + sizeof(unsigned short)), &type, sizeof(unsigned short));
            std::memcpy((void *)((char *)networkObject + sizeof(unsigned short) * 2), &component, sizeof(C));
            for (auto it : destination) {
                temporaryClient = getClientByHisId(it);
                transisthor_lib::sendDataToAClientWithoutCommunicator(
                    _communicator, temporaryClient, networkObject, ((sizeof(C)) + sizeof(unsigned short) * 2), 30);
            }
            return networkObject;
        }

        /// @brief Function called by the ECS. The transfered data will be converted to a Network object and send to the
        /// communicator.
        /// @tparam C Type of the resource
        /// @param id Id of the transfered resource
        /// @param type Type id of the resource
        /// @param resource The transfered resource
        template <std::derived_from<Resource> C>
        void transitEcsDataToNetworkData(unsigned short id, unsigned short type, C component)
        {
            (void)id;
            (void)component;
            (void)type;
            /// WILL BE IMPLEMENTED WHEN RESSOURCE HAVE BEEN MERGED.
        }

        /// @brief Function called by the ECS to transfer an order of creation for an AlliedProjectile entity
        /// @param id Id of the new entity to create
        /// @param allyId Id of the allied who fired
        /// @param uuid string representing the entity uuid (Used only for a first sync process in client side)
        /// @param destination of the message
        /// @return Return value his only used for testing (Unit and functional)
        void *transitEcsDataToNetworkDataEntityAlliedProjectile(
            unsigned short id, unsigned short allyId, std::string uuid, std::vector<unsigned short> destination);

        /// @brief Function called by the ECS to transfer an order of creation for an Enemy entity
        /// @param id Id of the new entity to create
        /// @param pos_x Position x of the Enemy
        /// @param pos_y Position y of the Enemy
        /// @param multiplierAbscissa The Velocity multiplierAbscissa for the new Enemy
        /// @param multiplierOrdinate The Velocity multiplierOrdinate for the new Enemy
        /// @param weight Weight of the Enemy
        /// @param size_x Size x of the Enemy
        /// @param size_y Size y of the Enemy
        /// @param life Life of the Enemy
        /// @param damage Damage of projectiles fired by this Enemy
        /// @param damageRadius DamageRadius of projectiles fired by this Enemy
        /// @param uuid string representing the entity uuid (Used only for a first sync process in client side)
        /// @param destination of the message
        /// @return Return value his only used for testing (Unit and functional)
        void *transitEcsDataToNetworkDataEntityEnemy(unsigned short id, int posX, int posY, double multiplierAbscissa,
            double multiplierOrdinate, short weight, int size_x, int size_y, short life, unsigned short damage,
            unsigned short damageRadius, std::string uuid, std::vector<unsigned short> destination);

        /// @brief Function called by the ECS to transfer an order of creation for an EnemyProjectile entity
        /// @param id Id of the new entity to create
        /// @param enemyId If of the enemy who fired
        /// @param uuid string representing the entity uuid (Used only for a first sync process in client side)
        /// @param destination of the message
        /// @return Return value his only used for testing (Unit and functional)
        void *transitEcsDataToNetworkDataEntityEnemyProjectile(
            unsigned short id, unsigned short enemyId, std::string uuid, std::vector<unsigned short> destination);

        /// @brief Function called by the ECS to transfer an order of creation for an Obstacle entity
        /// @param id Id of the new entity to create
        /// @param posX X value for the Position component
        /// @param posY Y value for the Position component
        /// @param damage Damage value of the Obstacle
        /// @param uuid string representing the entity uuid (Used only for a first sync process in client side)
        /// @param destination of the message
        /// @return Return value his only used for testing (Unit and functional)
        void *transitEcsDataToNetworkDataEntityObstacle(
            unsigned short id, int posX, int posY, unsigned short damage, std::string uuid, std::vector<unsigned short> destination);

        /// @brief Function called by the ECS to transfer an order of creation for an Player entity
        /// @param id Id of the new entity to create
        /// @param pos_x Position x of the Enemy
        /// @param pos_y Position y of the Enemy
        /// @param multiplierAbscissa The Velocity multiplierAbscissa for the new Enemy
        /// @param multiplierOrdinate The Velocity multiplierOrdinate for the new Enemy
        /// @param weight Weight of the Enemy
        /// @param size_x Size x of the Enemy
        /// @param size_y Size y of the Enemy
        /// @param life Life of the Enemy
        /// @param damage Damage of projectiles fired by this Enemy
        /// @param damageRadius DamageRadius of projectiles fired by this Enemy
        /// @param uuid string representing the entity uuid (Used only for a first sync process in client side)
        /// @param destination of the message
        /// @return Return value his only used for testing (Unit and functional)
        void *transitEcsDataToNetworkDataEntityPlayer(unsigned short id, int posX, int posY, double multiplierAbscissa,
            double multiplierOrdinate, short weight, int size_x, int size_y, short life, unsigned short damage,
            unsigned short damageRadius, std::string uuid, std::vector<unsigned short> destination);

        /// @brief Function called by the ECS to transfer an order of creation for an Projectile entity
        /// @param id Id of the new entity to create
        /// @param posX X value for the Position component
        /// @param posY Y value for the Position component
        /// @param velAbsc Abscissa value for the Velocity component
        /// @param velOrd Ordonate value for the Velocity component
        /// @param damage Damage value of the projectile
        /// @param uuid string representing the entity uuid (Used only for a first sync process in client side)
        /// @param destination of the message
        /// @return Return value his only used for testing (Unit and functional)
        void *transitEcsDataToNetworkDataEntityProjectile(unsigned short id, int posX, int posY, double velAbsc,
            double velOrd, unsigned short damage, std::string uuid, std::vector<unsigned short> destination);

        /// @brief Cross communicator client list and return the matched client
        /// @param id wanted id
        /// @return matched client
        /// @throw When no client his founded, throw a NetowkrError
        Client getClientByHisId(unsigned short id);

        /// @brief Function called inside ecs server to know server Endpoint id
        /// @return The server endpoint id
        /// @throw an error when no server can be found (Not in a client communicator), throw a NetworkError
        unsigned short getServerEndpointId(void);

      private:
        /// @brief A reference to a communicator
        Communicator &_communicator;

        /// @brief A reference to a Ecs World
        World &_ecsWorld;

        /// @brief Convert a byteCode data into a Destination component and send it to the ECS
        /// @param id Entity ID attached to the component
        /// @param byteCode byte value of the Destination component
        void componentConvertDestinationType(unsigned short id, void *byteCode);

        /// @brief Convert a byteCode data into a Equipment component and send it to the ECS
        /// @param id Entity ID attached to the component
        /// @param byteCode byte value of the Equipment component
        void componentConvertEquipmentType(unsigned short id, void *byteCode);

        /// @brief Convert a byteCode data into a Invinsible component and send it to the ECS
        /// @param id Entity ID attached to the component
        /// @param byteCode byte value of the Invinsible component
        void componentConvertInvinsibleType(unsigned short id, void *byteCode);

        /// @brief Convert a byteCode data into a Invisible component and send it to the ECS
        /// @param id Entity ID attached to the component
        /// @param byteCode byte value of the Invisible component
        void componentConvertInvisibleType(unsigned short id, void *byteCode);

        /// @brief Convert a byteCode data into a Life component and send it to the ECS
        /// @param id Entity ID attached to the component
        /// @param byteCode byte value of the Life component
        void componentConvertLifeType(unsigned short id, void *byteCode);

        /// @brief Convert a byteCode data into a Position component and send it to the ECS
        /// @param id Entity ID attached to the component
        /// @param byteCode byte value of the Position component
        void componentConvertPositionType(unsigned short id, void *byteCode);

        /// @brief Convert a byteCode data into a Velocity component and send it to the ECS
        /// @param id Entity ID attached to the component
        /// @param byteCode byte value of the Velocity component
        void componentConvertVelocityType(unsigned short id, void *byteCode);

        /// @brief Convert a byteCode data into a Death component and send it to the ECS
        /// @param id Entity ID attached to the component
        /// @param byteCode byte value of the Death component
        void componentConvertDeathType(unsigned short id, void *byteCode);

        /// @brief Convert a byteCode data into a AlliedProjectile entity and send it to the ECS
        /// @param id Entity ID attached to the entity
        /// @param byteCode byte value of the AlliedProjectile entity
        void entityConvertAlliedProjectileType(unsigned short id, void *byteCode);

        /// @brief Convert a byteCode data into a Enemy entity and send it to the ECS
        /// @param id Entity ID attached to the entity
        /// @param byteCode byte value of the Enemy entity
        void entityConvertEnemyType(unsigned short id, void *byteCode);

        /// @brief Convert a byteCode data into a EnemyProjectile entity and send it to the ECS
        /// @param id Entity ID attached to the entity
        /// @param byteCode byte value of the EnemyProjectile entity
        void entityConvertEnemyProjectileType(unsigned short id, void *byteCode);

        /// @brief Convert a byteCode data into a Obstacle entity and send it to the ECS
        /// @param id Entity ID attached to the entity
        /// @param byteCode byte value of the Obstacle entity
        void entityConvertObstacleType(unsigned short id, void *byteCode);

        /// @brief Convert a byteCode data into a Player entity and send it to the ECS
        /// @param id Entity ID attached to the entity
        /// @param byteCode byte value of the Player entity
        void entityConvertPlayerType(unsigned short id, void *byteCode);

        /// @brief Convert a byteCode data into a Projectile entity and send it to the ECS
        /// @param id Entity ID attached to the entity
        /// @param byteCode byte value of the Projectile entity
        void entityConvertProjectileType(unsigned short id, void *byteCode);

        /// @brief List of all the Convert function for Component. Ordered by the component type value (Refer to RFC for
        /// more informations)
        std::map<unsigned short, std::function<void(unsigned short, void *)>> _componentConvertFunctionList;

        /// @brief List of all the Convert function for Entity. Ordered by the entity type value (Refer to RFC for more
        /// informations)
        std::map<unsigned short, std::function<void(unsigned short, void *)>> _entityConvertFunctionList;
    };
} // namespace transisthor_lib

#endif /* !TRANSISTHOR_HPP_ */
