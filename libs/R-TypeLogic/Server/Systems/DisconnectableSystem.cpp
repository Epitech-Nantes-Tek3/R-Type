/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** DisconnectableSystem
*/

#include "DisconnectableSystem.hpp"
#include "R-TypeLogic/Global/Components/DeathComponent.hpp"
#include "R-TypeLogic/Global/Components/DisconnectableComponent.hpp"

using namespace ecs;

void DisconnectableSystem::run(World &world)
{
    std::vector<std::shared_ptr<ecs::Entity>> joined = world.joinEntities<Disconnectable>();

    auto disconnectableChange =
        [&world](std::shared_ptr<ecs::Entity> entityPtr) {
            entityPtr->removeComponent<Disconnectable>();
            entityPtr->addComponent<Death>();
            /// NB : WHEN A NEW RELATIVE OBJECT IS LINK TO A PLAYER, DONT FORGET TO ADD DEATH COMPONENT TO IT RIGHT
            /// THERE
        };

    std::for_each(joined.begin(), joined.end(), disconnectableChange);
}
