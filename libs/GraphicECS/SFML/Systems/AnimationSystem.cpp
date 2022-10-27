/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** AnimationSystem
*/

#include "AnimationSystem.hpp"
#include "GraphicsRectangleComponent.hpp"
// #include "AnimationDelayComponent.hpp"
#include "AnimationComponent.hpp"

using namespace ecs;

void AnimationSystem::run(World &world)
{
    std::vector<std::shared_ptr<Entity>> shapes = world.joinEntities<GraphicsRectangleComponent, AnimationComponent/*, AnimationDelayComponent*/>();
}