/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** ApplyInputDelay
*/

#ifndef APPLYINPUTDELAY_HPP_
#define APPLYINPUTDELAY_HPP_

#include "System/System.hpp"

namespace ecs
{
    class ApplyInputDelay : public System {
      public:
        void run(World &world) override final;
    };
} // namespace ecs

#endif /* !APPLYINPUTDELAY_HPP_ */
