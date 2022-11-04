/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** DeathLifeSystem
*/

#ifndef DEATHLIFESYSTEM_HPP_
#define DEATHLIFESYSTEM_HPP_

#include <mutex>
#include "Transisthor/TransisthorECSLogic/Server/Components/NetworkClient.hpp"
#include "World/World.hpp"
#include "R-TypeLogic/Global/Components/DeathComponent.hpp"
#include "R-TypeLogic/Global/Components/LifeComponent.hpp"
#include "R-TypeLogic/Global/Components/PlayerComponent.hpp"
#include <iostream>
namespace ecs
{
    /// @brief This is the DeathLife System.
    /// This System takes all entities that have a Life Component with 0 HP/life or less and adds a Death Component to
    /// them. It's a system that will be called by the engine world with the function runSystem()
    struct DeathLife : public System {
        inline void run(World &world) override final
        {
            std::vector<std::shared_ptr<ecs::Entity>> joined = world.joinEntities<Life>();

              std::cout << "test system death\n";
            auto deathlifetime = [&world](std::shared_ptr<ecs::Entity> entityPtr) {
                auto guard = std::lock_guard(*entityPtr.get());
                if (entityPtr.get()->getComponent<Life>().lifePoint <= 0 ) {
                    if (entityPtr->contains<Player>()) {
                        std::cout << "test01\n";
                        Client client = world.getTransisthorBridge()->getCommunicatorInstance().getClientByHisId(
                            entityPtr->getComponent<NetworkClient>().id);
                        std::cout << "test02\n";
                        world.getTransisthorBridge()->getCommunicatorInstance().sendDataToAClient(
                            client, nullptr, 0, 13);
                        entityPtr->getComponent<Life>().lifePoint = 1000;
                        std::cout << "test03\n";
                    } else {
                        std::cout << "test04\n";
                        entityPtr.get()->addComponent<Death>();
                        std::cout << "test05\n";
                    }
                }
            };
              std::cout << "test system death mid\n";
            auto test = [](std::shared_ptr<ecs::Entity> entityPtr) {
                if (entityPtr.get()->getComponent<Life>().lifePoint <= 0 ) {
                    std::cout << "test [\n";
                }
            };
            std::for_each(joined.begin(), joined.end(), test);
            std::for_each(joined.begin(), joined.end(), deathlifetime);
              std::cout << "test system death end\n";
        }
    };
} // namespace ecs

#endif /* !DEATHLIFESYSTEM_HPP_ */
