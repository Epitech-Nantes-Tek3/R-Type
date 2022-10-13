/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** RenderWindowResource
*/

#ifndef RENDERWINDOWRESOURCE_HPP_
#define RENDERWINDOWRESOURCE_HPP_

#include "Resource/Resource.hpp"
#include <SFML/Graphics.hpp>
#include <string>

namespace ecs
{
    /// @brief This shared resource adds a window.
    /// It will used by graphics part to draw something on screen, and get inputs on client part.
    /// It inherite from Resource class.
    class RenderWindowResource : public Resource {
        public:
            /// @brief Constructor of the render window resource class.
            /// @param title The title of the window as string. Set to "Default" as default.
            /// @param mode The screen mode. Set to "sf::VideoMode(1920, 1080, 32)" as default. See SFML documentation about sf::VideoMode for more information.
            /// @param style Set the style of the window. Set to "sf::Style::Default". See SFML documentation about sf::Style for more information.
            inline RenderWindowResource(std::string title = "Default", sf::VideoMode mode = sf::VideoMode(1920, 1080, 32), sf::Uint32 style = sf::Style::Default)
            {
                window.create(mode, title, sf::Style::Default);
            };

            /// @brief Default destructor.
            ~RenderWindowResource() = default;

            /// @brief The window to draw on or get inputs from it.
            sf::RenderWindow window;
    };
}

#endif /* !RENDERWINDOWRESOURCE_HPP_ */
