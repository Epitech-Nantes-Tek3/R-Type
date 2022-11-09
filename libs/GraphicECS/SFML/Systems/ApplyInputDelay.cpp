/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** ApplyInputDelay
*/

#include "ApplyInputDelay.hpp"
#include "GraphicECS/SFML/Components/InputDelayComponent.hpp"
#include "World/World.hpp"
#include "R-TypeLogic/Global/Components/VelocityComponent.hpp"

using namespace ecs;

void ApplyInputDelay::run(World &world)
{
    std::vector<std::shared_ptr<Entity>> entityVelocity =
        world.joinEntities<Velocity, graphicECS::SFML::Components::InputDelayComponent>();

    for (auto &it : entityVelocity) {
        it->getComponent<Velocity>().multiplierAbscissa =
            it->getComponent<graphicECS::SFML::Components::InputDelayComponent>().multiplierAbscissa;
        it->getComponent<Velocity>().multiplierOrdinate =
            it->getComponent<graphicECS::SFML::Components::InputDelayComponent>().multiplierOrdinate;
    }
}
