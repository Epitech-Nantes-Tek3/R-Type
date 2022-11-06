/*
** EPITECH PROJECT, 2022
** Project
** File description:
** ChatMessageComponent
*/

#ifndef CHATMESSAGECOMPONENT_HPP_
#define CHATMESSAGECOMPONENT_HPP_

namespace graphicECS::SFML::Components
{
    /// @brief This component class stores the content of a chat message component
    class ChatMessage : public ecs::Component {
      public:
        /// @brief author of the message
        std::string author;

        /// @brief Content of the message
        std::string message;

        /// @brief Constructor of ChatMessage object.
        /// @param auth Author name
        /// @param msg sended by the author
        ChatMessage(std::string auth, std::string msg) : author(auth), message(msg){};

        /// @brief Destroy the Writable Content object
        ~ChatMessage() = default;
    };
} // namespace graphicECS::SFML::Components

#endif /* !CHATMESSAGECOMPONENT_HPP_ */
