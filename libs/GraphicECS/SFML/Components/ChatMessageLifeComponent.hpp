/*
** EPITECH PROJECT, 2022
** R-Type [WSL : Ubuntu]
** File description:
** ChatMessageLifeComponent
*/

#ifndef CHATMESSAGELIFECOMPONENT_HPP_
#define CHATMESSAGELIFECOMPONENT_HPP_

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
        /// @param d Frequency to set the baseFrequency of the animation. Default value is 0.5 seconds.
        ChatMessageLife(const double &d = 5)
            : frequency(std::chrono::duration<double>(d)), baseFrequency(std::chrono::duration<double>(d)){};

        /// @brief Default destructor of ChatMessageLife.
        ~ChatMessageLife() = default;
    };
} // namespace graphicECS::SFML::Components

#endif /* !CHATMESSAGECOMPONENT_HPP_ */
