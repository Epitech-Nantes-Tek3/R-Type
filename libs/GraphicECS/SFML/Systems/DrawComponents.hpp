/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** DrawComponents
*/

#ifndef DRAWCOMPONENTS_HPP_
#define DRAWCOMPONENTS_HPP_

#include <SFML/Graphics.hpp>
#include "GraphicECS/SFML/Resources/RenderWindowResource.hpp"
#include "System/System.hpp"
#include "World/World.hpp"
#include "R-TypeLogic/Global/Components/LayerLvL.hpp"

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
        /// @param newFont the font to use
        static void addButtonText(std::shared_ptr<Entity> buttonPtr, const sf::Font &newFont);

        /// @brief Add corresponding texts to the writable thanks to its content
        /// @param writablePtr A Writable Entity
        /// @param newFont the font to use
        static void addWritableText(std::shared_ptr<Entity> writablePtr, const sf::Font &newFont);

        /// @brief Add corresponding texts to the chat message thanks to its chatMessage component
        /// @param chatMessagePtr A ChatMessage Entity
        /// @param newFont the font to use
        static void addChatMessageText(std::shared_ptr<Entity> chatMessagePtr, const sf::Font &newFont);

        /// @brief Add a text to the screen.
        /// @param textPtr A Text Entity
        /// @param newFont the font to use
        static void addText(std::shared_ptr<Entity> textPtr, const sf::Font &newFont);

        /// @brief The run function of this system. It will be used by the world in the function runSystems.
        /// @param world The corresponding world on which run this system.
        void run(World &world) override final;

      private:
        /// @brief Update entities which have a LayerLvL component set to PLAYER.
        /// @param layerType The layer type of the entity.
        /// @param entityPtr The entity to udpate.
        /// @param newFont font used to display the player name
        void _updatePlayer(LayerLvL &layerType, std::shared_ptr<ecs::Entity> entityPtr, const sf::Font &newFont);

        /// @brief Update entities which have a LayerLvL component set to ENEMY.
        /// @param layerType The layer type of the entity.
        /// @param entityPtr The entity to update.
        void _updateEnemy(LayerLvL &layerType, std::shared_ptr<ecs::Entity> entityPtr);

        /// @brief Update entities which have a LayerLvL component set to PROJECTILE.
        /// @param layerType The layer type of the entity.
        /// @param entityPtr The entity to update.
        void _udpateProjectile(LayerLvL &layerType, std::shared_ptr<ecs::Entity> entityPtr);

        /// @brief Update entities which have a LayerLvL component set to BUTTON.
        /// @param world The world on which the entity is.
        /// @param layerType The layer type of the entity.
        /// @param entityPtr The entity to update.
        void _updateButton(World &world, LayerLvL &layerType, std::shared_ptr<ecs::Entity> entityPtr);

        /// @brief Update entities which have a LayerLvL component set to WRITABLE.
        /// @param world The world on which the entity is.
        /// @param layerType The layer type of the entity.
        /// @param entityPtr The entity to update.
        void _updateWritable(World &world, LayerLvL &layerType, std::shared_ptr<ecs::Entity> entityPtr);

        /// @brief Update entities which have a LayerLvL component set to TEXT and CHAT_MESSAGE.
        /// @param world The world on which the entity is.
        /// @param layerType The layer type of the entity.
        /// @param entityPtr The entity to update.
        void _updateText(World &world, LayerLvL &layerType, std::shared_ptr<ecs::Entity> entityPtr);

        /// @brief Call all the update entities functions to.
        /// @param world The world on which entities are.
        /// @param entityPtr The entity to update.
        void _updateEntities(World &world, std::shared_ptr<ecs::Entity> entityPtr);

        /// @brief Draw a component on the window.
        /// @param world The world on which the entity is.
        /// @param entityPtr The entity to draw.
        /// @param renderWindow The window on which the entity will be drawn.
        void _drawComponent(World &world, std::shared_ptr<ecs::Entity> entityPtr,
            graphicECS::SFML::Resources::RenderWindowResource &windowResource);

        /// @brief Draw a rectangle on the window.
        /// @param world The world on which the entity is.
        /// @param entityPtr The entity to draw.
        /// @param windowResource The window on which the entity will be drawn.
        void _drawRectangle(World &world, std::shared_ptr<ecs::Entity> entityPtr,
            graphicECS::SFML::Resources::RenderWindowResource &windowResource);

        /// @brief Draw a text on the window.
        /// @param world The world on which the entity is.
        /// @param entityPtr The entity to draw.
        /// @param windowResource The window on which the entity will be drawn.
        void _drawText(World &world, std::shared_ptr<ecs::Entity> entityPtr,
            graphicECS::SFML::Resources::RenderWindowResource &windowResource);

        /// @brief Update texture on a shape.
        /// @param world The world on which the entity is.
        /// @param entityPtr The entity to update.
        /// @param windowResource The window on which the entity will be drawn.
        void _updateTexture(World &world, std::shared_ptr<ecs::Entity> entityPtr);
    };
} // namespace graphicECS::SFML::Systems

#endif /* !DRAWCOMPONENTS_HPP_ */
