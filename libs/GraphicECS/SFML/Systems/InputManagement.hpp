/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** InputManagement
*/

#ifndef INPUTMANAGEMENT_HPP_
#define INPUTMANAGEMENT_HPP_

#include "System/System.hpp"
#include "World/World.hpp"
#include "R-TypeLogic/EntityManipulation/CreateEntitiesFunctions/CreateAlliedProjectile.hpp"
#include "R-TypeLogic/Global/Components/ControlableComponent.hpp"
#include "R-TypeLogic/Global/Components/VelocityComponent.hpp"

namespace ecs
{
    /// @brief This system class manage SFML input to link them to an action.
    struct InputManagement : public System {
      public:
        /// @brief The run function of this system. It will be used by the world in the function runSystems.
        /// @param world The corresponding world on which run this system.
        void run(World &world) override final;

        /// @brief This function is call when a player move his Abscissa with a input
        /// @param world The world in which the Player is
        /// @param move Action velocity
        void movePlayerX(World &world, float move);

        /// @brief This function is call when a player move his Ordinate with a input
        /// @param world The world in which the Player is
        /// @param move Action velocity
        void movePlayerY(World &world, float move);

        /// @brief This function is call when a player shoot with a input. It creates a Ally Projectile
        /// @param world The world in which the Player is
        /// @param move Action Shoot
        void shootAction(World &world, float action);

      private:
        void _closeWindow(sf::Event &event, World &world);
        void _keyPressedEvents(sf::Event &event, std::vector<std::shared_ptr<Entity>> &Inputs);
        void _keyReleasedEvents(sf::Event &event, std::vector<std::shared_ptr<Entity>> &Inputs);
    };
} // namespace ecs

#endif /* !INPUTMANAGEMENT_HPP_ */
