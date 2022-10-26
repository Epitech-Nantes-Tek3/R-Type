/*
** EPITECH PROJECT, 2022
** Project
** File description:
** ButtonAction
*/

#include "ButtonAction.hpp"
#include "GraphicECS/SFML/Resources/RenderWindowResource.hpp"

void exitWindow(World &world)
{
    // TO CHANGE WHEN PROPER HANDLE OF SIGINT WILL BE IMPLEMENTED
    world.getResource<RenderWindowResource>().window.close();
}
