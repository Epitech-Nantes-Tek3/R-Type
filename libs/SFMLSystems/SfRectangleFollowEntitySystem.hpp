/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** SfRectangleFollowEntitySystem
*/

#ifndef SFRECTANGLEFOLLOWENTITYSYSTEM_HPP_
#define SFRECTANGLEFOLLOWENTITYSYSTEM_HPP_

#include <SFML/Graphics.hpp>
#include "Component/Component.hpp"
#include "GameComponents/PositionComponent.hpp"
#include "SFMLComponents/GraphicsRectangleComponent.hpp"
#include "System/System.hpp"
#include "World/World.hpp"

namespace ecs
{
    /// @brief This system class manage SFML Rectangle Shape to modify it's SfRectangleSahpePosition with the Position
    /// of the Entity
    struct SfRectangleFollowEntitySystem : public System {
        /// @brief The run function of this system. It will be used by the world in the function runSystems.
        /// @param world The corresponding world on which run this system.
        void run(World &world) override final;
    };
} // namespace ecs

#endif /* !SFRECTANGLEFOLLOWENTITYSYSTEM_HPP_ */
