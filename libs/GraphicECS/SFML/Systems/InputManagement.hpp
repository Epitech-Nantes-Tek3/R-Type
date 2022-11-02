/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** InputManagement
*/

#ifndef INPUTMANAGEMENT_HPP_
#define INPUTMANAGEMENT_HPP_

#include <SFML/Graphics.hpp>
#include "System/System.hpp"
#include "World/World.hpp"
#include "R-TypeLogic/EntityManipulation/CreateEntitiesFunctions/CreateAlliedProjectile.hpp"
#include "R-TypeLogic/Global/Components/ControlableComponent.hpp"
#include "R-TypeLogic/Global/Components/VelocityComponent.hpp"
#include "GraphicECS/SFML/Resources/RenderWindowResource.hpp"

namespace graphicECS::SFML::Systems
{
    /// @brief This system class manage SFML input to link them to an action.
    struct InputManagement : public System {
      public:
        /// @brief The run function of this system. It will be used by the world in the function runSystems.
        /// @param world The corresponding world on which run this system.
        void run(World &world) override final;

        /// @brief This function is called when a player move his Abscissa with a input
        /// @param world The world in which the Player is
        /// @param move Action velocity
        void movePlayerX(World &world, float move);

        /// @brief This function is called when a player move his Ordinate with a input
        /// @param world The world in which the Player is
        /// @param move Action velocity
        void movePlayerY(World &world, float move);

        /// @brief This function is called when a player shoot with a input. It creates a Ally Projectile
        /// @param world The world in which the Player is
        /// @param move Action Shoot
        void shootAction(World &world, float action);

        /// @brief This function is called when a player wants to exit the game. It closes the window of the client
        /// @param world The world where the window exists
        void exit(World &world);

        /// @brief This function is called when a left click occurs
        /// @param world The world where the click occurs
        /// @param action The click action
        void clickHandle(World &world, float action);
      private:

        /// @brief This function shoot if the player is shooting and the frequency allow a shoot
        /// @param world The world used to create a new projectile entity
        void shoot(World &world);

        /// @brief This function closes the window when event type is sf::Event::Closed
        /// @param event Class event use to know SFML events
        /// @param windowResource The window to be closed
        void _closeWindow(sf::Event &event, graphicECS::SFML::Resources::RenderWindowResource &windowResource);

        /// @brief This function manages key pressed events. It adds an action to do in a queue depending on the key
        /// pressed type.
        /// @param event Class event use to know SFML events
        /// @param Inputs Entity which contains inputs entity like mouse, keyboard and controller
        void _keyPressedEvents(sf::Event &event, std::vector<std::shared_ptr<Entity>> &Inputs);

        /// @brief This function manages key released events. It adds an action to do in a queue depending on the key
        /// released type.
        /// @param event Class event use to know SFML events
        /// @param Inputs Entity which contains inputs entity like mouse, keyboard and controller
        void _keyReleasedEvents(sf::Event &event, std::vector<std::shared_ptr<Entity>> &Inputs);

        /// @brief This function manages mouse button pressed events. It adds an action to do in a queue depending on
        /// the mouse button type.
        /// @param event Class event use to know SFML events
        /// @param Inputs Entity which contains inputs entity like mouse, keyboard and controller
        void _mouseEvents(sf::Event &event, std::vector<std::shared_ptr<Entity>> &Inputs);
    };
} // namespace graphicECS::SFML::Systems

#endif /* !INPUTMANAGEMENT_HPP_ */
