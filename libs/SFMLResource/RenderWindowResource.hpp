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
    class RenderWindowResource : public Resource {
        public:
            RenderWindowResource(std::string title = "Default", sf::VideoMode mode = sf::VideoMode(1920, 1080, 32), sf::Uint32 style = sf::Style::Default)
            {
                window.create(mode, title, sf::Style::Default);
            };
            ~RenderWindowResource() = default;
            sf::RenderWindow window;
    };
}

#endif /* !RENDERWINDOWRESOURCE_HPP_ */
