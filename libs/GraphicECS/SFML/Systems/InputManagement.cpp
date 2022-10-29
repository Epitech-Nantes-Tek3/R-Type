/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** InputManagement
*/

#include "InputManagement.hpp"
#include <chrono>
#include <mutex>
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
#include "R-TypeLogic/EntityManipulation/ButtonManipulation/SharedResources/ButtonActionMap.hpp"
#include "R-TypeLogic/EntityManipulation/ButtonManipulation/Components/DisplayState.hpp"
#include "R-TypeLogic/Global/Components/ButtonComponent.hpp"
#include "R-TypeLogic/Global/Components/ShootingFrequencyComponent.hpp"
#include "R-TypeLogic/Global/SharedResources/GameClock.hpp"

using namespace graphicECS::SFML::Resources;
using namespace graphicECS::SFML::Components;

namespace graphicECS::SFML::Systems
{
    void InputManagement::_closeWindow(sf::Event &event, World &world)
    {
        if (event.type == sf::Event::Closed) {
            RenderWindowResource &windowResource = world.getResource<RenderWindowResource>();
            auto guard = std::lock_guard(windowResource);
            windowResource.window.close();
        }
    }

    void InputManagement::_keyPressedEvents(sf::Event &event, std::vector<std::shared_ptr<Entity>> &Inputs)
    {
        if (event.type == sf::Event::KeyPressed) {
            auto keyPressed = [event](std::shared_ptr<Entity> entityPtr) {
                std::lock_guard(*entityPtr.get());
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
            auto keyReleased = [event](std::shared_ptr<Entity> entityPtr) {
                std::lock_guard(*entityPtr.get());
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
            auto mouseButtonPressed = [event](std::shared_ptr<Entity> entityPtr) {
                std::lock_guard(*entityPtr.get());
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
        while (world.containsResource<RenderWindowResource>()) {
            RenderWindowResource &windowResource = world.getResource<RenderWindowResource>();
            auto guard = std::lock_guard(windowResource);
            if (!windowResource.window.pollEvent(event))
                break;
            _closeWindow(event, world);
            _keyPressedEvents(event, Inputs);
            _keyReleasedEvents(event, Inputs);
            _mouseEvents(event, Inputs);
        }
        for (auto &entityPtr : Inputs) {
            std::lock_guard(*entityPtr.get());
            std::queue<std::pair<ActionQueueComponent::inputAction_e, float>> &actions =
                entityPtr->getComponent<ActionQueueComponent>().actions;
            while (actions.size() > 0) {
                if (world.getResource<MenuStates>().currentState == MenuStates::IN_GAME) {
                    if (actions.front().first == ActionQueueComponent::MOVEY)
                        movePlayerY(world, actions.front().second);
                    if (actions.front().first == ActionQueueComponent::MOVEX)
                        movePlayerX(world, actions.front().second);
                    if (actions.front().first == ActionQueueComponent::SHOOT)
                        shootAction(world, actions.front().second);
                }
                if (actions.front().first == ActionQueueComponent::BUTTON_CLICK) {
                    clickHandle(world, actions.front().second);
                }
                actions.pop();
            }
        }
    }

    void InputManagement::movePlayerX(World &world, float move)
    {
        std::vector<std::shared_ptr<Entity>> player = world.joinEntities<Controlable>();
        double moveD = double(move);

        if (player.empty())
            return;
        auto moveX = [moveD](std::shared_ptr<Entity> entityPtr) {
            std::lock_guard(*entityPtr.get());
            entityPtr->getComponent<Velocity>().multiplierAbscissa = moveD;
            entityPtr->getComponent<Velocity>().modified = true;
            entityPtr->getComponent<Position>().modified = true;
        };
        std::for_each(player.begin(), player.end(), moveX);
    }

    void InputManagement::movePlayerY(World &world, float move)
    {
        std::vector<std::shared_ptr<Entity>> player = world.joinEntities<Controlable>();
        double moveD = double(move);

        if (player.empty())
            return;
        auto moveY = [moveD](std::shared_ptr<Entity> entityPtr) {
            std::lock_guard(*entityPtr.get());
            entityPtr->getComponent<Velocity>().multiplierOrdinate = moveD;
            entityPtr->getComponent<Velocity>().modified = true;
            entityPtr->getComponent<Position>().modified = true;
        };
        std::for_each(player.begin(), player.end(), moveY);
    }

    void InputManagement::shootAction(World &world, float action)
    {
        std::vector<std::shared_ptr<Entity>> player = world.joinEntities<Controlable>();

        if (player.empty() || action < 1)
            return;
        auto shoot = [&world](std::shared_ptr<Entity> entityPtr) {
            std::lock_guard(*entityPtr.get());
            ShootingFrequency &freq = entityPtr.get()->getComponent<ShootingFrequency>();
            const char hex_char[] = "0123456789ABCDEF";
            RandomDevice &random = world.getResource<RandomDevice>();
            auto guard = std::lock_guard(random);
            std::string uuid(16, '\0');

            if (freq.frequency == duration<double>(0.0)) {
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
        RenderWindowResource &windowResource = world.getResource<RenderWindowResource>();
        auto guard = std::lock_guard(windowResource);
        sf::Vector2i mousePos = sf::Mouse::getPosition(windowResource.window);

        auto clickInButton = [this, &world, &mousePos](std::shared_ptr<Entity> entityPtr) {
            std::lock_guard(*entityPtr.get());
            Position &pos = entityPtr.get()->getComponent<Position>();
            Size &size = entityPtr.get()->getComponent<Size>();
            DisplayState &state = entityPtr.get()->getComponent<DisplayState>();

            bool sameWidth = pos.y <= mousePos.y && mousePos.y <= pos.y + size.y;
            bool sameHeigth = pos.x <= mousePos.x && mousePos.x <= pos.x + size.x;

            if (sameHeigth && sameWidth && state.displayState == world.getResource<MenuStates>().currentState) {
                ActionName &name = entityPtr.get()->getComponent<ActionName>();
                ButtonActionMap &map = world.getResource<ButtonActionMap>();
                auto guard = std::lock_guard(map);

                std::function<void(World &)> fct = map.actionList.find(name.actionName)->second;
                fct(world);
            }
        };
        std::for_each(joined.begin(), joined.end(), clickInButton);
    }
} // namespace graphicECS::SFML::Systems
