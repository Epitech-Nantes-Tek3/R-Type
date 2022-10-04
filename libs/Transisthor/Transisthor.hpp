/*
** EPITECH PROJECT, 2022
** Project
** File description:
** Transisthor
*/

/// @file libs/Transisthor/Transisthor.hpp

#ifndef TRANSISTHOR_HPP_
#define TRANSISTHOR_HPP_

#include "Communicator/Communicator.hpp"
#include "World/World.hpp"

using namespace ecs;
using namespace communicator_lib;

namespace transisthor_lib
{
    class Transisthor {
      public:
        /// @brief Construct a new Transisthor object
        /// @param communicator A reference to a working communicator
        /// @param ecsWorld A reference to a working ecs
        inline Transisthor(Communicator &communicator, World &ecsWorld) : _communicator(communicator), _ecsWorld(ecsWorld) {};

        /// @brief Destroy a Transisthor object (Default value)
        ~Transisthor() = default;

        /// @brief Function called by the Communicator. The transfered data will be converted to an ECS object and send to the ecs.
        /// @param networkData Content of the network data (Refer to communicator lib document for more details)
        void transitNetworkDataToEcsData(Message networkData);

        /// @brief Function called by the ECS. The transfered data will be converted to a Network object and send to the communicator.
        /// @tparam C Type of the component
        /// @param id Id of the transfered component
        /// @param type Type id of the component
        /// @param component The transfered component
        template <std::derived_from<Component> C>
        void transitEcsDataToNetworkData(unsigned short id, unsigned short type, C component)
        {
            (void) id;
            (void) type;
            (void) component;
        }

        /// @brief Function called by the ECS. The transfered data will be converted to a Network object and send to the communicator.
        /// @tparam C Type of the resource
        /// @param id Id of the transfered resource
        /// @param type Type id of the resource
        /// @param resource The transfered resource
        template <std::derived_from<Resource> C>
        void transitEcsDataToNetworkData(unsigned short id, unsigned short type, C component)
        {
            (void) id;
            (void) component;
            (void) type;
        }

        /// @brief Function called by the ECS. The transfered data will be converted to a Network object and send to the communicator.
        /// @tparam ...Args This allow to send multiple Component (Used for an entity)
        /// @tparam C Type of the component
        /// @param id Id of the transfered entity
        /// @param type Type id of the transfered entity
        /// @param ...args All components used inside the wanted entity.
        template<std::derived_from<Component>... C>
        void transitEcsDataToNetworkData(unsigned short id, unsigned short type, C &&...args)
        {
            (void) id;
            (void) type;
        }

      private:
        /// @brief A reference to a communicator
        Communicator &_communicator;

        /// @brief A reference to a Ecs World
        World &_ecsWorld;

    };
} // namespace transisthor_lib

#endif /* !TRANSISTHOR_HPP_ */
