/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** RemoveChatSystem
*/

#ifndef REMOVECHATSYSTEM_HPP_
#define REMOVECHATSYSTEM_HPP_

#include "System/System.hpp"
#include "World/World.hpp"

namespace graphicECS::SFML::Systems
{
    /// @brief This structure system updates the ChatMessageLife frequency and remove the dead one
    struct RemoveChatSystem : public ecs::System {
        /// @brief It is used by the world to run this system. It updates ChatMessageLife.
        /// @param world The corresponding world on which run this system.
        void run(World &world) override final;

      private:
        void _updateFrequency(World &world, std::shared_ptr<ecs::Entity> entity);
    };
} // namespace graphicECS::SFML::Systems

#endif /* !REMOVECHATSYSTEM_HPP_ */
