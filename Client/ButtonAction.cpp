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
    auto &resource = world.getResource<RenderWindowResource>();
    auto guard = std::lock_guard(resource);
    resource.window.close();
}
