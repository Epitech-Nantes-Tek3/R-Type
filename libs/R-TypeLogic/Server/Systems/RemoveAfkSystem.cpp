/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** RemoveAfkSystem
*/

#include "RemoveAfkSystem.hpp"
#include "Transisthor/TransisthorECSLogic/Server/Components/NetworkClient.hpp"
#include "R-TypeLogic/Server/Components/AfkFrequencyComponent.hpp"

using namespace ecs;

void RemoveAfkSystem::run(World &world)
{
    std::vector<std::shared_ptr<ecs::Entity>> joined = world.joinEntities<AfkFrequency>();

    auto afkHandle = [&world](std::shared_ptr<ecs::Entity> entityPtr) {
        AfkFrequency &freq = entityPtr.get()->getComponent<AfkFrequency>();

        if (freq.frequency == duration<double>(0)) {
            Client client = world.getTransisthorBridge()->getCommunicatorInstance().getClientByHisId(entityPtr->getComponent<NetworkClient>().id);

            world.getTransisthorBridge()->getCommunicatorInstance().sendDataToAClient(client, nullptr, 0, 13);
            freq.frequency = freq.baseFrequency;
        }
    };

    std::for_each(joined.begin(), joined.end(), afkHandle);
}
