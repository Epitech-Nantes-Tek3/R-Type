/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** InputManagement
*/

#include "InputManagement.hpp"
#include "ActionQueueComponent.hpp"
#include "AllowControllerComponent.hpp"
#include "AllowMouseAndKeyboardComponent.hpp"
#include "ControllerButtonInputComponent.hpp"
#include "ControllerJoystickInputComponent.hpp"
#include "KeyboardInputComponent.hpp"
#include "MouseInputComponent.hpp"
#include "SFMLResource/RenderWindowResource.hpp"
#include "World/World.hpp"

using namespace ecs;

void InputManagement::run(World &world)
{
    sf::Event event;
    std::vector<std::shared_ptr<Entity>> Inputs = world.joinEntities<MouseInputComponent, KeyboardInputComponent,
        ControllerButtonInputComponent, ControllerJoystickInputComponent, ActionQueueComponent>();

    while (world.getResource<RenderWindowResource>().window.pollEvent(event)) {
        if (event.type == sf::Event::KeyPressed) {
            auto keyPressed = [event](std::shared_ptr<ecs::Entity> entityPtr) {
                if (entityPtr->getComponent<KeyboardInputComponent>().keyboardMapActions.contains(event.key.code)
                    && entityPtr->contains<AllowMouseAndKeyboardComponent>())
                    entityPtr->getComponent<ActionQueueComponent>().actions.push(
                        entityPtr->getComponent<KeyboardInputComponent>().keyboardMapActions[event.key.code].first);
            };
            std::for_each(Inputs.begin(), Inputs.end(), keyPressed);
        }
        if (event.type == sf::Event::MouseButtonPressed) {
            auto mouseButtonPressed = [event](std::shared_ptr<ecs::Entity> entityPtr) {
                if (entityPtr->getComponent<MouseInputComponent>().MouseMapActions.contains(event.mouseButton.button)
                    && entityPtr->contains<AllowMouseAndKeyboardComponent>())
                    entityPtr->getComponent<ActionQueueComponent>().actions.push(
                        entityPtr->getComponent<MouseInputComponent>().MouseMapActions[event.mouseButton.button].first);
            };
            std::for_each(Inputs.begin(), Inputs.end(), mouseButtonPressed);
        }
        if (event.type == sf::Event::JoystickButtonPressed) {
            auto joyButtonPressed = [event](std::shared_ptr<ecs::Entity> entityPtr) {
                if (entityPtr->getComponent<ControllerButtonInputComponent>().controllerButtonMapActions.contains(
                        event.joystickButton.button)
                    && entityPtr->contains<AllowControllerComponent>())
                    entityPtr->getComponent<ActionQueueComponent>().actions.push(
                        entityPtr->getComponent<ControllerButtonInputComponent>()
                            .controllerButtonMapActions[event.joystickButton.button]
                            .first);
            };
            std::for_each(Inputs.begin(), Inputs.end(), joyButtonPressed);
        }
        if (event.type == sf::Event::JoystickMoved) {
            auto joyMovePressed = [event](std::shared_ptr<ecs::Entity> entityPtr) {
                if (entityPtr->getComponent<ControllerJoystickInputComponent>().controllerJoystickMapActions.contains(
                        event.joystickMove.axis)
                    && entityPtr->contains<AllowControllerComponent>())
                    entityPtr->getComponent<ActionQueueComponent>().actions.push(
                        entityPtr->getComponent<ControllerJoystickInputComponent>()
                            .controllerJoystickMapActions[event.joystickMove.axis]
                            .first);
            };
            std::for_each(Inputs.begin(), Inputs.end(), joyMovePressed);
        }
    }
}

void InputManagement::movePlayerX(World &world, float move)
{
    std::vector<std::shared_ptr<ecs::Entity>> player = world.joinEntities<Controlable>();
    double moveD = double(move);

    auto moveX = [moveD](std::shared_ptr<ecs::Entity> entityPtr) {
        entityPtr->getComponent<Velocity>().multiplierAbscissa = moveD;
    };
    std::for_each(player.begin(), player.end(), moveX);
}

void InputManagement::movePlayerY(World &world, float move)
{
    std::vector<std::shared_ptr<ecs::Entity>> player = world.joinEntities<Controlable>();
    double moveD = double(move);

    auto moveY = [moveD](std::shared_ptr<ecs::Entity> entityPtr) {
        entityPtr->getComponent<Velocity>().multiplierOrdinate = moveD;
    };
    std::for_each(player.begin(), player.end(), moveY);
}

void InputManagement::shootAction(World &world, float action)
{
    std::vector<std::shared_ptr<ecs::Entity>> player = world.joinEntities<Controlable>();
    (void)action;

    auto shoot = [&world](
                     std::shared_ptr<ecs::Entity> entityPtr) { createNewAlliedProjectile(world, *entityPtr.get()); };
    std::for_each(player.begin(), player.end(), shoot);
}