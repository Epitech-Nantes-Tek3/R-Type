/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** TextComponent
*/

#ifndef TEXTCOMPONENT_HPP_
#define TEXTCOMPONENT_HPP_

#include <string>
#include "Component/Component.hpp"

namespace ecs
{
    /// @brief A class that inherits from Component. It has a public string text and a constructor that takes a string
    /// as a parameter.
    class TextComponent : public Component {
      public:
        /// @brief Store a text to be drawn.
        std::string text;

        /// @brief Contruct a new text component.
        /// @param t The text to set. Default value: "Default".
        inline TextComponent(const std::string &t = "Default") : text(t){};

        /// @brief Default destructor.
        ~TextComponent() = default;
    };
} // namespace ecs

#endif /* !TEXTCOMPONENT_HPP_ */
