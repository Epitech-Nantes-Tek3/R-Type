/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** SfObjectFollowEntitySystem
*/

#ifndef _SFOBJECTFOLLOWENTITY_HPP_
#define _SFOBJECTFOLLOWENTITY_HPP_

#include <SFML/Graphics.hpp>
#include "Component/Component.hpp"
#include "GraphicECS/SFML/Components/GraphicsRectangleComponent.hpp"
#include "GraphicECS/SFML/Components/GraphicsTextComponent.hpp"
#include "System/System.hpp"
#include "World/World.hpp"
#include "R-TypeLogic/Global/Components/PositionComponent.hpp"
#include "R-TypeLogic/Global/Components/SizeComponent.hpp"
#include "R-TypeLogic/Global/Components/VelocityComponent.hpp"

namespace graphicECS::SFML::Systems
{
    /// @brief This system class manage SFML Rectangle Shape to modify it's SfRectangleSahpePosition with the Position
    /// of the Entity
    struct SfObjectFollowEntitySystem : public System {
        /// @brief The run function of this system. It will be used by the world in the function runSystems.
        /// @param world The corresponding world on which run this system.
        void run(World &world) override final;
    };
} // namespace graphicECS::SFML::Systems

#endif /* !_SFOBJECTFOLLOWENTITY_HPP_ */
