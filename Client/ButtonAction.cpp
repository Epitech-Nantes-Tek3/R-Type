/*
** EPITECH PROJECT, 2022
** Project
** File description:
** ButtonAction
*/

#include "ButtonAction.hpp"
#include <mutex>
#include "GraphicECS/SFML/Resources/RenderWindowResource.hpp"

using namespace graphicECS::SFML::Resources;

void exitWindow(World &world)
{
    (void)world;
    std::raise(SIGINT);
}
