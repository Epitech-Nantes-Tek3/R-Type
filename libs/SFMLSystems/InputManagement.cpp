/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** InputManagement
*/

#include "InputManagement.hpp"
#include "World/World.hpp"
#include "RenderWindowResource.hpp"

using namespace ecs;

void InputManagement::run(World &world)
{
    sf::Event event;

    while (world.getResource<RenderWindowResource>().window.pollEvent(event)) {
        
    }
}