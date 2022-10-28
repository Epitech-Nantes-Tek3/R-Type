/*
** EPITECH PROJECT, 2022
** Project
** File description:
** ButtonAction
*/

#include "ButtonAction.hpp"
#include "GraphicECS/SFML/Resources/RenderWindowResource.hpp"
#include <boost/asio/thread_pool.hpp>

using namespace graphicECS::SFML::Resources;

void exitWindow(World &world)
{
    // TO CHANGE WHEN PROPER HANDLE OF SIGINT WILL BE IMPLEMENTED
    // At this moment, we can't lock the resource here because we can't close the window
    // This will be fixed when the above change will be implemented
    RenderWindowResource &resource = world.getResource<RenderWindowResource>();
    resource.window.close();
}
