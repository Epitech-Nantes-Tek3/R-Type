/*
** EPITECH PROJECT, 2022
** R-Type [WSL : Ubuntu]
** File description:
** ChatMessageLifeComponent
*/

#ifndef CHATMESSAGECOMPONENT_HPP_
#define CHATMESSAGECOMPONENT_HPP_

#include <vector>
#include "Component/Component.hpp"

namespace graphicECS::SFML::Components
{
    /// @brief This component stores the life frequency of a chat message entity
    class ChatMessageLife : public ecs::Component {
      public:
        /// @brief The current life duration in seconds.
        std::chrono::duration<double> frequency;

        /// @brief The default life duration in seconds.
        const std::chrono::duration<double> baseFrequency;

        /// @brief Default constructor of ChatMessageLife.
        ChatMessageLife(const double &d = 5)
            : frequency(std::chrono::duration<double>(d)), baseFrequency(std::chrono::duration<double>(d)){};

        /// @brief Default destructor of ChatMessageLife.
        ~ChatMessageLife() = default;
    };
} // namespace graphicECS::SFML::Components

#endif /* !CHATMESSAGECOMPONENT_HPP_ */
