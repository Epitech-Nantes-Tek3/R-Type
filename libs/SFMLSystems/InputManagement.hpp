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
    class InputManagement : public System {
        public:
            InputManagement() = default;
            ~InputManagement() = default;
            void run(World &world);
    };
}

#endif /* !INPUTMANAGEMENT_HPP_ */
