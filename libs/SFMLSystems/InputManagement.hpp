/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** InputManagement
*/

#ifndef INPUTMANAGEMENT_HPP_
#define INPUTMANAGEMENT_HPP_

#include "GameComponents/ControlableComponent.hpp"
#include "GameComponents/VelocityComponent.hpp"
#include "GameEntityManipulation/CreateEntitiesFunctions/CreateAlliedProjectile.hpp"
#include "System/System.hpp"
#include "World/World.hpp"

namespace ecs
{
    /// @brief This system class manage SFML input to link them to an action.
    struct InputManagement : public System {
        /// @brief The run function of this system. It will be used by the world in the function runSystems.
        /// @param world The corresponding world on which run this system.
        void run(World &world) override final;

        /// @brief This function is call when a player move his Abscissa with a input
        /// @param world The world in which the Player is
        /// @param move Action velocity 
        inline void movePlayerX(World &world, float move)
        {
            std::vector<std::shared_ptr<ecs::Entity>> player = world.joinEntities<Controlable>();
            double move_d = double(move);

            auto moveX = [move_d](std::shared_ptr<ecs::Entity> entityPtr) {
                entityPtr->getComponent<Velocity>().multiplierAbscissa = move_d;
            };
            std::for_each(player.begin(), player.end(), moveX);
        }

        /// @brief This function is call when a player move his Ordinate with a input
        /// @param world The world in which the Player is
        /// @param move Action velocity 
        inline void movePlayerY(World &world, float move)
        {
            std::vector<std::shared_ptr<ecs::Entity>> player = world.joinEntities<Controlable>();
            double move_d = double(move);

            auto moveY = [move_d](std::shared_ptr<ecs::Entity> entityPtr) {
                entityPtr->getComponent<Velocity>().multiplierOrdinate = move_d;
            };
            std::for_each(player.begin(), player.end(), moveY);
        }

        /// @brief This function is call when a player shoot with a input. It creates a Ally Projectile
        /// @param world The world in which the Player is
        /// @param move Action Shoot 
        inline void shootAction(World &world, float action)
        {
            std::vector<std::shared_ptr<ecs::Entity>> player = world.joinEntities<Controlable>();

            auto shoot = [&world](std::shared_ptr<ecs::Entity> entityPtr) {
                createNewAlliedProjectile(world, *entityPtr.get());
            };
        }
    };
} // namespace ecs

#endif /* !INPUTMANAGEMENT_HPP_ */
