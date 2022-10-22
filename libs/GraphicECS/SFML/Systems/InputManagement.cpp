/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** InputManagement
*/

#include "InputManagement.hpp"
#include <chrono>
#include <random>
#include <string.h>
#include "ActionQueueComponent.hpp"
#include "AllowControllerComponent.hpp"
#include "AllowMouseAndKeyboardComponent.hpp"
#include "ControllerButtonInputComponent.hpp"
#include "ControllerJoystickInputComponent.hpp"
#include "KeyboardInputComponent.hpp"
#include "MouseInputComponent.hpp"
#include "GameComponents/ShootingFrequencyComponent.hpp"
#include "GameSharedResources/GameClock.hpp"
#include "GraphicECS/SFML/Resources/RenderWindowResource.hpp"
#include "World/World.hpp"

using namespace ecs;

void InputManagement::run(World &world)
{
    sf::Event event;
    std::vector<std::shared_ptr<Entity>> Inputs = world.joinEntities<MouseInputComponent, KeyboardInputComponent,
        ControllerButtonInputComponent, ControllerJoystickInputComponent, ActionQueueComponent>();

    if (Inputs.empty())
        return;
    while (world.getResource<RenderWindowResource>().window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            world.getResource<RenderWindowResource>().window.close();
        if (event.type == sf::Event::KeyPressed) {
            auto keyPressed = [event](std::shared_ptr<ecs::Entity> entityPtr) {
                if (entityPtr->getComponent<KeyboardInputComponent>().keyboardMapActions.contains(event.key.code)
                    && entityPtr->contains<AllowMouseAndKeyboardComponent>())
                    entityPtr->getComponent<ActionQueueComponent>().actions.push(
                        entityPtr->getComponent<KeyboardInputComponent>().keyboardMapActions[event.key.code]);
            };
            std::for_each(Inputs.begin(), Inputs.end(), keyPressed);
        }
        if (event.type == sf::Event::KeyReleased) {
            auto keyReleased = [event](std::shared_ptr<ecs::Entity> entityPtr) {
                if (entityPtr->getComponent<KeyboardInputComponent>().keyboardMapActions.contains(event.key.code)
                    && entityPtr->contains<AllowMouseAndKeyboardComponent>()) {
                    entityPtr->getComponent<ActionQueueComponent>().actions.push(
                        std::make_pair<ActionQueueComponent::inputAction_e, float>(
                            ActionQueueComponent::inputAction_e(entityPtr->getComponent<KeyboardInputComponent>()
                                                                    .keyboardMapActions[event.key.code]
                                                                    .first),
                            0));
                }
            };
            std::for_each(Inputs.begin(), Inputs.end(), keyReleased);
        }
        if (event.type == sf::Event::MouseButtonPressed) {
            auto mouseButtonPressed = [event](std::shared_ptr<ecs::Entity> entityPtr) {
                if (entityPtr->getComponent<MouseInputComponent>().MouseMapActions.contains(event.mouseButton.button)
                    && entityPtr->contains<AllowMouseAndKeyboardComponent>()) {}
                // entityPtr->getComponent<ActionQueueComponent>().actions.push(
                //     entityPtr->getComponent<MouseInputComponent>().MouseMapActions[event.mouseButton.button]);
            };
            std::for_each(Inputs.begin(), Inputs.end(), mouseButtonPressed);
        }
        if (event.type == sf::Event::JoystickButtonPressed) {
            auto joyButtonPressed = [event](std::shared_ptr<ecs::Entity> entityPtr) {
                if (entityPtr->getComponent<ControllerButtonInputComponent>().controllerButtonMapActions.contains(
                        event.joystickButton.button)
                    && entityPtr->contains<AllowControllerComponent>()) {}
                // entityPtr->getComponent<ActionQueueComponent>().actions.push(
                //     entityPtr->getComponent<ControllerButtonInputComponent>()
                //         .controllerButtonMapActions[event.joystickButton.button]);
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
                            .controllerJoystickMapActions[event.joystickMove.axis]);
            };
            std::for_each(Inputs.begin(), Inputs.end(), joyMovePressed);
        }
    }
    for (auto &entityPtr : Inputs) {
        std::queue<std::pair<ecs::ActionQueueComponent::inputAction_e, float>> &actions =
            entityPtr->getComponent<ActionQueueComponent>().actions;
        while (actions.size() > 0) {
            if (actions.front().first == ActionQueueComponent::MOVEY)
                movePlayerY(world, actions.front().second);
            if (actions.front().first == ActionQueueComponent::MOVEX)
                movePlayerX(world, actions.front().second);
            if (actions.front().first == ActionQueueComponent::SHOOT)
                shootAction(world, actions.front().second);
            actions.pop();
        }
    }
}

void InputManagement::movePlayerX(World &world, float move)
{
    std::vector<std::shared_ptr<ecs::Entity>> player = world.joinEntities<Controlable>();
    double moveD = double(move);

    if (player.empty())
        return;
    auto moveX = [moveD](std::shared_ptr<ecs::Entity> entityPtr) {
        entityPtr->getComponent<Velocity>().multiplierAbscissa = moveD;
        entityPtr->getComponent<Velocity>().modified = true;
        entityPtr->getComponent<Position>().modified = true;
    };
    std::for_each(player.begin(), player.end(), moveX);
}

void InputManagement::movePlayerY(World &world, float move)
{
    std::vector<std::shared_ptr<ecs::Entity>> player = world.joinEntities<Controlable>();
    double moveD = double(move);

    if (player.empty())
        return;
    auto moveY = [moveD](std::shared_ptr<ecs::Entity> entityPtr) {
        entityPtr->getComponent<Velocity>().multiplierOrdinate = moveD;
        entityPtr->getComponent<Velocity>().modified = true;
        entityPtr->getComponent<Position>().modified = true;
    };
    std::for_each(player.begin(), player.end(), moveY);
}

void InputManagement::shootAction(World &world, float action)
{
    std::vector<std::shared_ptr<ecs::Entity>> player = world.joinEntities<Controlable>();
    (void)action;

    if (player.empty())
        return;
    auto shoot = [&world](std::shared_ptr<ecs::Entity> entityPtr) {
        ShootingFrequency &freq = entityPtr.get()->getComponent<ShootingFrequency>();
        GameClock &c = world.getResource<GameClock>();

        double delta = freq.frequency.count() - c.getElapsedTime();
        if (delta <= 0.0) {
            const char hex_char[] = "0123456789ABCDEF";
            auto &temp = world.getResource<RandomDevice>();

            std::string uuid(16, '\0');
            for (auto &c : uuid)
                c = hex_char[temp.randInt<int>(0, 15)];
            createNewAlliedProjectile(world, *entityPtr, uuid);
            freq.frequency = freq.baseFrequency;
        } else {
            freq.frequency = duration<double>(delta);
        }
    };
    std::for_each(player.begin(), player.end(), shoot);
}