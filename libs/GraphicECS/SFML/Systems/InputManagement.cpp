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
#include "KeyboardInputComponent.hpp"
#include "MouseInputComponent.hpp"
#include "World/World.hpp"
#include "R-TypeLogic/EntityManipulation/ButtonManipulation/Components/ActionName.hpp"
#include "R-TypeLogic/EntityManipulation/ButtonManipulation/Components/DisplayState.hpp"
#include "R-TypeLogic/EntityManipulation/ButtonManipulation/SharedResources/ButtonActionMap.hpp"
#include "R-TypeLogic/Global/Components/ButtonComponent.hpp"
#include "R-TypeLogic/Global/Components/ShootingFrequencyComponent.hpp"
#include "R-TypeLogic/Global/SharedResources/GameClock.hpp"
#include "IsShootingComponent.hpp"

using namespace graphicECS::SFML::Resources;
using namespace graphicECS::SFML::Components;

namespace graphicECS::SFML::Systems
{
    void InputManagement::_closeWindow(sf::Event &event, RenderWindowResource &windowResource)
    {
        if (event.type == sf::Event::Closed) {
            windowResource.window.close();
        }
    }

    void InputManagement::_keyPressedEvents(sf::Event &event, std::vector<std::shared_ptr<Entity>> &Inputs)
    {
        if (event.type == sf::Event::KeyPressed) {
            for (auto entityPtr : Inputs) {
                auto keyboardMapActions = entityPtr->getComponent<KeyboardInputComponent>().keyboardMapActions;

                if (keyboardMapActions.contains(event.key.code)
                    && entityPtr->contains<AllowMouseAndKeyboardComponent>()) {
                    auto guard = std::lock_guard(*entityPtr.get());
                    entityPtr->getComponent<ActionQueueComponent>().actions.push(keyboardMapActions[event.key.code]);
                }
            }
        }
    }

    void InputManagement::_keyReleasedEvents(sf::Event &event, std::vector<std::shared_ptr<Entity>> &Inputs)
    {
        if (event.type == sf::Event::KeyReleased) {
            for (auto entityPtr : Inputs) {
                auto keyboardMapActions = entityPtr->getComponent<KeyboardInputComponent>().keyboardMapActions;

                if (keyboardMapActions.contains(event.key.code)
                    && entityPtr->contains<AllowMouseAndKeyboardComponent>()) {
                    auto guard = std::lock_guard(*entityPtr.get());
                    entityPtr->getComponent<ActionQueueComponent>().actions.push(
                        std::make_pair<ActionQueueComponent::inputAction_e, float>(
                            ActionQueueComponent::inputAction_e(keyboardMapActions[event.key.code].first), 0));
                }
            }
        }
    }

    void InputManagement::_mouseEvents(sf::Event &event, std::vector<std::shared_ptr<Entity>> &Inputs)
    {
        if (event.type == sf::Event::MouseButtonPressed) {
            for (auto entityPtr : Inputs) {
                if (entityPtr->getComponent<MouseInputComponent>().MouseMapActions.contains(event.mouseButton.button)
                    && entityPtr->contains<AllowMouseAndKeyboardComponent>()) {
                    auto guard = std::lock_guard(*entityPtr.get());
                    entityPtr->getComponent<ActionQueueComponent>().actions.push(
                        entityPtr->getComponent<MouseInputComponent>().MouseMapActions[event.mouseButton.button]);
                }
            }
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
            {
                auto guard = std::lock_guard(windowResource);
                if (!windowResource.window.pollEvent(event))
                    break;
            }
            _closeWindow(event, windowResource);
            _keyPressedEvents(event, Inputs);
            _keyReleasedEvents(event, Inputs);
            _mouseEvents(event, Inputs);
        }
        for (auto &entityPtr : Inputs) {
            std::queue<std::pair<ActionQueueComponent::inputAction_e, float>> &actions =
                entityPtr->getComponent<ActionQueueComponent>().actions;
            std::queue<std::pair<ActionQueueComponent::inputAction_e, float>> newActions;

            while (actions.size() > 0) {
                std::cout << "debug3 start" << std::endl;
                MenuStates &menuState = world.getResource<MenuStates>();
                MenuStates::menuState_e currState = menuState.currentState;
                std::cout << "debug3 after lock" << std::endl;

                if (currState == MenuStates::IN_GAME) {
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
                std::cout << "debug3 pop" << std::endl;
                {
                    auto entity_guard = std::lock_guard(*entityPtr.get());
                    actions.pop();
                }
                std::cout << "debug3 end" << std::endl;
            }
        }
        shoot(world);
    }

    void InputManagement::shoot(World &world)
    {
        std::vector<std::shared_ptr<Entity>> player = world.joinEntities<Controlable>();

        if (player.empty())
            return;
        auto shoot = [&world](std::shared_ptr<Entity> entityPtr) {
            if (entityPtr->contains<IsShootingComponent>()) {
                std::cout << "debug2" << std::endl;
                ShootingFrequency &freq = entityPtr.get()->getComponent<ShootingFrequency>();
                const char hex_char[] = "0123456789ABCDEF";
                RandomDevice &random = world.getResource<RandomDevice>();
                std::string uuid(16, '\0');

                if (freq.frequency == duration<double>(0.0)) {
                    for (auto &c : uuid) {
                        auto guard = std::lock_guard(random);
                        c = hex_char[random.randInt<int>(0, 15)];
                    }
                    createNewAlliedProjectile(world, *entityPtr, uuid);
                    {
                        auto entityGuard = std::lock_guard(*entityPtr.get());
                        freq.frequency = freq.baseFrequency;
                    }
                }
            }
        };
        std::for_each(player.begin(), player.end(), shoot);
    }

    void InputManagement::movePlayerX(World &world, float move)
    {
        std::cout << "debug4 start" << std::endl;
        std::vector<std::shared_ptr<Entity>> player = world.joinEntities<Controlable>();
        double moveD = double(move);

        if (player.empty())
            return;
        std::cout << "debug4 update" << std::endl;
        auto moveX = [moveD](std::shared_ptr<Entity> entityPtr) {
            auto guard = std::lock_guard(*entityPtr.get());
            entityPtr->getComponent<Velocity>().multiplierAbscissa = moveD;
            entityPtr->getComponent<Velocity>().modified = true;
            entityPtr->getComponent<Position>().modified = true;
        };
        std::for_each(player.begin(), player.end(), moveX);
        std::cout << "debug4 end" << std::endl;
    }

    void InputManagement::movePlayerY(World &world, float move)
    {
        std::cout << "debug4 start" << std::endl;
        std::vector<std::shared_ptr<Entity>> player = world.joinEntities<Controlable>();
        double moveD = double(move);

        if (player.empty())
            return;
        std::cout << "debug4 update" << std::endl;
        auto moveY = [moveD](std::shared_ptr<Entity> entityPtr) {
            auto guard = std::lock_guard(*entityPtr.get());
            entityPtr->getComponent<Velocity>().multiplierOrdinate = moveD;
            entityPtr->getComponent<Velocity>().modified = true;
            entityPtr->getComponent<Position>().modified = true;
        };
        std::for_each(player.begin(), player.end(), moveY);
        std::cout << "debug4 end" << std::endl;
    }

    void InputManagement::shootAction(World &world, float action)
    {
        std::vector<std::shared_ptr<Entity>> player = world.joinEntities<Controlable>();

        if (player.empty())
            return;
        for (std::shared_ptr<ecs::Entity> p : player) {
            std::cout << "debug1" << std::endl;
            if (action > 1 && !(p->contains<IsShootingComponent>())) {
                std::lock_guard(*p.get());
                p->addComponent<IsShootingComponent>();
            } else if ( action < 1 && p->contains<IsShootingComponent>()) {
                std::lock_guard(*p.get());
                p->removeComponent<IsShootingComponent>();
            }
        }
    }

    void InputManagement::clickHandle(World &world, float action)
    {
        (void)action;
        std::vector<std::shared_ptr<Entity>> joined = world.joinEntities<Button, Position, Size>();
        RenderWindowResource &windowResource = world.getResource<RenderWindowResource>();
        sf::Vector2i mousePos = sf::Mouse::getPosition(windowResource.window);

        auto clickInButton = [this, &world, &mousePos](std::shared_ptr<Entity> entityPtr) {
            Position &pos = entityPtr.get()->getComponent<Position>();
            Size &size = entityPtr.get()->getComponent<Size>();
            DisplayState &state = entityPtr.get()->getComponent<DisplayState>();

            bool sameWidth = pos.y <= mousePos.y && mousePos.y <= pos.y + size.y;
            bool sameHeigth = pos.x <= mousePos.x && mousePos.x <= pos.x + size.x;
            MenuStates &menuState = world.getResource<MenuStates>();
            MenuStates::menuState_e currState = menuState.currentState;
            if (sameHeigth && sameWidth && state.displayState == currState) {
                ActionName &name = entityPtr.get()->getComponent<ActionName>();
                ButtonActionMap &map = world.getResource<ButtonActionMap>();

                std::function<void(World &)> fct = map.actionList.find(name.actionName)->second;
                fct(world);
            }
        };
        std::for_each(joined.begin(), joined.end(), clickInButton);
    }
} // namespace graphicECS::SFML::Systems
