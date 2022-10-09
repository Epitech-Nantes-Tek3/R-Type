/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** ActionQueueComponent
*/

#ifndef ACTIONQUEUECOMPONENT_HPP_
#define ACTIONQUEUECOMPONENT_HPP_

#include "ECSActions.hpp"
#include "Component/Component.hpp"
#include <queue>
#include <functional>

namespace ecs
{
    /// @brief This component class stores a function queue.
    /// These functions will be added when an input occurs during the game by a system.
    /// They will be used by another system.
    /// These function are stored in ECSActions.hpp
    class ActionQueueComponent : public Component {
        public:
            /// @brief This action queue stores function that will be called in a system and added by another one when inputs occur.
            std::queue<std::function<void()>> actions;

            /// @brief Default constructor.
            ActionQueueComponent() = default;

            /// @brief Default destructor.
            ~ActionQueueComponent() = default;
    };
} // namespace ecs

#endif /* !ACTIONQUEUECOMPONENT_HPP_ */
