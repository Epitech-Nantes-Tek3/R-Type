/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** DrawComponents
*/

#ifndef DRAWCOMPONENTS_HPP_
#define DRAWCOMPONENTS_HPP_

#include <SFML/Graphics.hpp>
#include "System/System.hpp"
#include "World/World.hpp"
#include "R-TypeLogic/Global/Components/LayerLvL.hpp"
#include "GraphicECS/SFML/Resources/RenderWindowResource.hpp"

namespace graphicECS::SFML::Systems
{
    /// @brief This class draw GraphicsComponents on window.
    struct DrawComponents : public System {
        /// @brief Compare layer value to be sorted in run function.
        /// @param e1 Value 1 to be compared.
        /// @param e2 Value 2 to be compared.
        /// @return return true if value 1 is greater than value 2, false otherwise
        static bool compareLayer(std::shared_ptr<Entity> e1, std::shared_ptr<Entity> e2);

        /// @brief Add corresponding texts to the button thanks to its action
        /// @param buttonPtr A Button Entity
        static void addButtonText(std::shared_ptr<Entity> buttonPtr, const sf::Font &newFont);

        /// @brief The run function of this system. It will be used by the world in the function runSystems.
        /// @param world The corresponding world on which run this system.
        void run(World &world) override final;

      private:
        void _updatePlayer(LayerLvL &layerType, std::shared_ptr<ecs::Entity> entityPtr);
        void _updateEnemy(LayerLvL &layerType, std::shared_ptr<ecs::Entity> entityPtr);
        void _udpateProjectile(LayerLvL &layerType, std::shared_ptr<ecs::Entity> entityPtr);
        void _updateButton(World &world, LayerLvL &layerType, std::shared_ptr<ecs::Entity> entityPtr);
        void _updateEntities(World &world, std::shared_ptr<ecs::Entity> entityPtr);
        void _drawComponent(World &world, std::shared_ptr<ecs::Entity> entityPtr, graphicECS::SFML::Resources::RenderWindowResource &windowResource);
    };
} // namespace graphicECS::SFML::Systems

#endif /* !DRAWCOMPONENTS_HPP_ */
