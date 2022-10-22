/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** ParallaxSystem
*/

#include "ParallaxSystem.hpp"
#include "GameComponents/PositionComponent.hpp"
#include "GraphicECS/SFML/Components/ParallaxComponent.hpp"

#define MAXIMUM_WIDTH 1920

void Parallax::run(World &world)
{
    std::vector<std::shared_ptr<ecs::Entity>> joined = world.joinEntities<ParallaxBackground>();

    auto makeParallax = [](std::shared_ptr<ecs::Entity> entityPtr) {
        Position &pos = entityPtr.get()->getComponent<Position>();

        if (pos.x <= MAXIMUM_WIDTH * -1) {
            pos.x = MAXIMUM_WIDTH;
        }
    };

    std::for_each(joined.begin(), joined.end(), makeParallax);
}