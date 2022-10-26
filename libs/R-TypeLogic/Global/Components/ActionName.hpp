/*
** EPITECH PROJECT, 2022
** Project
** File description:
** ActionName
*/

#ifndef ACTIONNAME_HPP_
#define ACTIONNAME_HPP_

#include "Component/Component.hpp"
#include "R-TypeLogic/Global/SharedResources/ButtonActionMap.hpp"

namespace ecs
{
    /// @brief Action Name stores the key as enum to the corresponding action
    /// It can be an exit action, an opening menu action, a close menu action...
    class ActionName : public Component {
      public:
        /// @brief The Texture name stored to find the action
        ButtonActionMap::buttonAction_e actionName;

        /// @brief Constructor of the ActionName Component
        /// @param newActionName The value to be set in the Action List corresponding to an action
        ActionName(ButtonActionMap::buttonAction_e newActionName = ButtonActionMap::buttonAction_e::UNDEFINED)
            : actionName(newActionName){};

        /// @brief Default Destructor
        ~ActionName() = default;
    };
} // namespace ecs

#endif /* !ACTIONNAME_HPP_ */
