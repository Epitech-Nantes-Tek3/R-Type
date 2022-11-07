/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** WritableContentComponent
*/

#ifndef WRITABLECONTENTCOMPONENT_HPP_
#define WRITABLECONTENTCOMPONENT_HPP_

namespace graphicECS::SFML::Components
{
    /// @brief This component class stores the content of a writable component
    class WritableContent : public ecs::Component {
      public:
        /// @brief A string containing all the typed content
        std::string content;

        /// @brief Constructor of WritableContentComponent.
        inline WritableContent() { content = std::string(0, '\0'); };

        /// @brief Destroy the Writable Content object
        ~WritableContent() = default;
    };
} // namespace graphicECS::SFML::Components

#endif /* !WRITABLECONTENTCOMPONENT_HPP_ */
