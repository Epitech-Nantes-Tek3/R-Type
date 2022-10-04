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

      private:
        /// @brief A reference to a communicator
        Communicator &_communicator;

        /// @brief A reference to a Ecs World
        World &_ecsWorld;

    };
} // namespace transisthor_lib

#endif /* !TRANSISTHOR_HPP_ */
