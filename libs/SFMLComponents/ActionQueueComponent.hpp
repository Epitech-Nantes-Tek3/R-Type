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
    class ActionQueueComponent : public Component {
        public:
            std::queue<std::function<void()>> actions;
            ActionQueueComponent() = default;
            ~ActionQueueComponent() = default;
    };
}

#endif /* !ACTIONQUEUECOMPONENT_HPP_ */
