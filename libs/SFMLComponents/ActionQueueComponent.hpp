/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** ActionQueueComponent
*/

#ifndef ACTIONQUEUECOMPONENT_HPP_
#define ACTIONQUEUECOMPONENT_HPP_

#include <functional>
#include <queue>
#include "Component/Component.hpp"
#include "World/World.hpp"

namespace ecs
{
    /// @brief This component class stores a function queue.
    /// These functions will be added when an input occurs during the game by a system.
    /// They will be used by another system.
    /// These function are stored in ECSActions.hpp
    class ActionQueueComponent : public Component {
      public:
        /// @brief This action queue stores function that will be called in a system and added by another one when
        /// inputs occur.
        // std::queue<std::function<void(World &, float)>> actions;
        enum inputAction_e {UNDEFINED, MOVEX, MOVEY, SHOOT, MAX_ACTION};
        std::queue<std::pair<inputAction_e, float>> actions;
        /// @brief Default constructor.
        ActionQueueComponent() = default;

        /// @brief Default destructor.
        ~ActionQueueComponent() = default;
    };
} // namespace ecs

#endif /* !ACTIONQUEUECOMPONENT_HPP_ */
