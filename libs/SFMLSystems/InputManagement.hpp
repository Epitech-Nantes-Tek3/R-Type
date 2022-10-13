/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** InputManagement
*/

#ifndef INPUTMANAGEMENT_HPP_
#define INPUTMANAGEMENT_HPP_

#include "System/System.hpp"

namespace ecs
{
    /// @brief This system class manage SFML input to link them to an action.
    class InputManagement : public System {
        public:
            /// @brief Default constructor of the InputManagement
            InputManagement() = default;

            /// @brief Default destructor of the InputManagement
            ~InputManagement() = default;

            /// @brief The run function of this system. It will be used by the world in the function runSystems.
            /// @param world The corresponding world on which run this system.
            void run(World &world);
    };
} // namespace

#endif /* !INPUTMANAGEMENT_HPP_ */
