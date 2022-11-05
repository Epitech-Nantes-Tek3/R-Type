/*
** EPITECH PROJECT, 2022
** Project
** File description:
** WritableButtonActionComponent
*/

#ifndef WRITABLEBUTTONACTIONCOMPONENT_HPP_
#define WRITABLEBUTTONACTIONCOMPONENT_HPP_

namespace graphicECS::SFML::Components
{
    /// @brief This component class stores the action to execute when a writable button action is pressed
    class WritableButtonAction : public ecs::Component {
      public:
        /// @brief Function to execute when a writtable button entity is pressed
        std::function<void(World &, Entity &, std::string &)> actionToExecute;

        /// @brief Constructor of WritableButtonActionComponent.
        inline WritableButtonAction(std::function<void(World &, Entity &, std::string &)> actionParam)
        {
            actionToExecute = actionParam;
        };

        /// @brief Destroy the WritableButtonAction object
        ~WritableButtonAction() = default;
    };
} // namespace graphicECS::SFML::Components

#endif /* !WRITABLEBUTTONACTIONCOMPONENT_HPP_ */
