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
    /// @brief A system that is used to apply the input delay to the player.
    class ApplyInputDelay : public System {
      public:
        /// @brief It applies the input delay to the velocity of the entity
        /// @param world The world in which the system is running.
        void run(World &world) override final;
    };
} // namespace ecs

#endif /* !APPLYINPUTDELAY_HPP_ */
