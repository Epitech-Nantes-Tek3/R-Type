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
#include "GraphicECS/SFML/Resources/RenderWindowResource.hpp"
#include "KeyboardInputComponent.hpp"
#include "MouseInputComponent.hpp"
#include "World/World.hpp"
#include "R-TypeLogic/EntityManipulation/ButtonManipulation/Components/ActionName.hpp"
#include "R-TypeLogic/Global/Components/ButtonComponent.hpp"
#include "R-TypeLogic/Global/Components/ShootingFrequencyComponent.hpp"
#include "R-TypeLogic/EntityManipulation/ButtonManipulation/SharedResources/ButtonActionMap.hpp"
#include "R-TypeLogic/Global/SharedResources/GameClock.hpp"

namespace ecs
{
    void InputManagement::_closeWindow(sf::Event &event, World &world)
    {
        if (event.type == sf::Event::Closed)
            world.getResource<RenderWindowResource>().window.close();
    }

    void InputManagement::_keyPressedEvents(sf::Event &event, std::vector<std::shared_ptr<Entity>> &Inputs)
    {
        if (event.type == sf::Event::KeyPressed) {
            auto keyPressed = [event](std::shared_ptr<ecs::Entity> entityPtr) {
                if (entityPtr->getComponent<KeyboardInputComponent>().keyboardMapActions.contains(event.key.code)
                    && entityPtr->contains<AllowMouseAndKeyboardComponent>())
                    entityPtr->getComponent<ActionQueueComponent>().actions.push(
                        entityPtr->getComponent<KeyboardInputComponent>().keyboardMapActions[event.key.code]);
            };
            std::for_each(Inputs.begin(), Inputs.end(), keyPressed);
        }
    }

    void InputManagement::_keyReleasedEvents(sf::Event &event, std::vector<std::shared_ptr<Entity>> &Inputs)
    {
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
    }

    void InputManagement::_mouseEvents(sf::Event &event, std::vector<std::shared_ptr<Entity>> &Inputs)
    {
        if (event.type == sf::Event::MouseButtonPressed) {
            auto mouseButtonPressed = [event](std::shared_ptr<ecs::Entity> entityPtr) {
                if (entityPtr->getComponent<MouseInputComponent>().MouseMapActions.contains(event.mouseButton.button)
                    && entityPtr->contains<AllowMouseAndKeyboardComponent>()) {
                    entityPtr->getComponent<ActionQueueComponent>().actions.push(
                        entityPtr->getComponent<MouseInputComponent>().MouseMapActions[event.mouseButton.button]);
                }
            };
            std::for_each(Inputs.begin(), Inputs.end(), mouseButtonPressed);
        }
    }

    void InputManagement::run(World &world)
    {
        sf::Event event;
        std::vector<std::shared_ptr<Entity>> Inputs = world.joinEntities<MouseInputComponent, KeyboardInputComponent,
            ControllerButtonInputComponent, ControllerJoystickInputComponent, ActionQueueComponent>();

        if (Inputs.empty())
            return;
        while (world.containsResource<RenderWindowResource>()
            && world.getResource<RenderWindowResource>().window.pollEvent(event)) {
            _closeWindow(event, world);
            _keyPressedEvents(event, Inputs);
            _keyReleasedEvents(event, Inputs);
            _mouseEvents(event, Inputs);
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
                if (actions.front().first == ActionQueueComponent::BUTTON_CLICK) {
                    clickHandle(world, actions.front().second);
                }
                actions.pop();
            }
        }
        std::vector<std::shared_ptr<ecs::Entity>> players = world.joinEntities<Controlable>();
        for (auto &player : players) {
            ShootingFrequency &freq = player->getComponent<ShootingFrequency>();
            GameClock &clock = world.getResource<GameClock>();
            double delta = freq.frequency.count() - clock.getElapsedTime();
            freq.frequency = duration<double>(delta);
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

        if (player.empty() || action < 1)
            return;
        auto shoot = [&world](std::shared_ptr<ecs::Entity> entityPtr) {
            ShootingFrequency &freq = entityPtr.get()->getComponent<ShootingFrequency>();
            const char hex_char[] = "0123456789ABCDEF";
            ecs::RandomDevice &random = world.getResource<RandomDevice>();
            std::string uuid(16, '\0');

            if (freq.frequency.count() <= 0.0) {
                for (auto &c : uuid)
                    c = hex_char[random.randInt<int>(0, 15)];
                createNewAlliedProjectile(world, *entityPtr, uuid);
                freq.frequency = freq.baseFrequency;
            }
        };
        std::for_each(player.begin(), player.end(), shoot);
    }

    void InputManagement::clickHandle(World &world, float action)
    {
        (void)action;
        std::vector<std::shared_ptr<Entity>> joined = world.joinEntities<Button, Position, Size>();
        sf::Vector2i mousePos = sf::Mouse::getPosition(world.getResource<RenderWindowResource>().window);

        auto clickInButton = [this, &world, &mousePos](std::shared_ptr<Entity> entityPtr) {
            Position &pos = entityPtr.get()->getComponent<Position>();
            Size &size = entityPtr.get()->getComponent<Size>();
            bool sameWidth = pos.y <= mousePos.y && mousePos.y <= pos.y + size.y;
            bool sameHeigth = pos.x <= mousePos.x && mousePos.x <= pos.x + size.x;

            if (sameHeigth && sameWidth) {
                ActionName &name = entityPtr.get()->getComponent<ActionName>();
                ButtonActionMap &map = world.getResource<ButtonActionMap>();

                std::function<void(World &)> fct = map.actionList.find(name.actionName)->second;

                fct(world);
            }
        };
        std::for_each(joined.begin(), joined.end(), clickInButton);
    }
} // namespace ecs
