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
#include "GraphicECS/SFML/Components/GraphicsTextComponent.hpp"
#include "GraphicECS/SFML/Components/InputDelayComponent.hpp"
#include "GraphicECS/SFML/Components/TextureName.hpp"
#include "IsShootingComponent.hpp"
#include "KeyboardInputComponent.hpp"
#include "MouseInputComponent.hpp"
#include "SelectedComponent.hpp"
#include "World/World.hpp"
#include "WritableContentComponent.hpp"
#include "R-TypeLogic/EntityManipulation/ButtonManipulation/Components/ActionName.hpp"
#include "R-TypeLogic/EntityManipulation/ButtonManipulation/Components/DisplayState.hpp"
#include "R-TypeLogic/EntityManipulation/ButtonManipulation/SharedResources/ButtonActionMap.hpp"
#include "R-TypeLogic/Global/Components/ButtonComponent.hpp"
#include "R-TypeLogic/Global/Components/ShootingFrequencyComponent.hpp"
#include "R-TypeLogic/Global/SharedResources/GameClock.hpp"

using namespace graphicECS::SFML::Resources;
using namespace graphicECS::SFML::Components;

namespace graphicECS::SFML::Systems
{
    void InputManagement::_closeWindow(sf::Event &event, RenderWindowResource &windowResource)
    {
        if (event.type == sf::Event::Closed) {
            windowResource.window.close();
#ifdef __linux__
            std::raise(SIGINT);
#endif
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

    void InputManagement::_textEnteredEvents(sf::Event &event, std::vector<std::shared_ptr<Entity>> joined)
    {
        if (event.type == sf::Event::TextEntered) {
            auto writeText = [&event](std::shared_ptr<Entity> entityPtr) {
                auto &writableContent = entityPtr->getComponent<WritableContent>();

                if (event.text.unicode == 8 && writableContent.content.size() != 0) {
                    auto guard = std::lock_guard(*entityPtr.get());
                    writableContent.content.pop_back();
                } else if (event.text.unicode == 13) {
                    auto guard = std::lock_guard(*entityPtr.get());
                    entityPtr->removeComponent<Selected>();
                    if (entityPtr->contains<TextureName>())
                        entityPtr->getComponent<TextureName>().textureName = GraphicsTextureResource::WRITABLE;
                    return;
                } else if (event.text.unicode != 8) {
                    auto guard = std::lock_guard(*entityPtr.get());
                    writableContent.content.resize(writableContent.content.size() + 1, (char)event.text.unicode);
                }
                if (entityPtr->contains<GraphicsTextComponent>()) {
                    auto &textComponent = entityPtr->getComponent<GraphicsTextComponent>();
                    unsigned short textLen = 0;
                    std::string formatedText = writableContent.content;

                    for (; writableContent.content[textLen] != '\0'; textLen++)
                        ;
                    formatedText.resize(textLen);
                    textComponent.text.setString(formatedText);
                }
            };

            std::for_each(joined.begin(), joined.end(), writeText);
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

    void InputManagement::_controllerEvents(sf::Event &event, std::vector<std::shared_ptr<Entity>> &Inputs)
    {
        if (event.type == sf::Event::JoystickMoved) {
            for (auto entityPtr : Inputs) {
                if (entityPtr->getComponent<ControllerJoystickInputComponent>().controllerJoystickMapActions.contains(
                        event.joystickMove.axis)
                    && entityPtr->contains<AllowControllerComponent>()) {
                    auto guard = std::lock_guard(*entityPtr.get());
                    entityPtr->getComponent<ControllerJoystickInputComponent>()
                        .controllerJoystickMapActions[event.joystickMove.axis]
                        .second = event.joystickMove.position;
                    entityPtr->getComponent<ActionQueueComponent>().actions.push(
                        entityPtr->getComponent<ControllerJoystickInputComponent>()
                            .controllerJoystickMapActions[event.joystickMove.axis]);
                }
            }
        }
        if (event.type == sf::Event::JoystickButtonPressed) {
            for (auto entityPtr : Inputs) {
                if (entityPtr->getComponent<ControllerButtonInputComponent>().controllerButtonMapActions.contains(
                        event.joystickMove.axis)
                    && entityPtr->contains<AllowControllerComponent>()) {
                    auto guard = std::lock_guard(*entityPtr.get());
                    entityPtr->getComponent<ActionQueueComponent>().actions.push(
                        entityPtr->getComponent<ControllerButtonInputComponent>()
                            .controllerButtonMapActions[event.joystickButton.button]);
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
            std::vector<std::shared_ptr<Entity>> joined = world.joinEntities<WritableContent, Selected>();
            _closeWindow(event, windowResource);
            if (joined.empty()) {
                _keyPressedEvents(event, Inputs);
                _keyReleasedEvents(event, Inputs);
                _controllerEvents(event, Inputs);
            } else {
                _textEnteredEvents(event, joined);
            }
            _mouseEvents(event, Inputs);
        }
        for (auto &entityPtr : Inputs) {
            std::queue<std::pair<ActionQueueComponent::inputAction_e, float>> &actions =
                entityPtr->getComponent<ActionQueueComponent>().actions;
            std::queue<std::pair<ActionQueueComponent::inputAction_e, float>> newActions;

            while (actions.size() > 0) {
                MenuStates &menuState = world.getResource<MenuStates>();
                MenuStates::menuState_e currState = menuState.currentState;

                if (currState == MenuStates::SOLO_GAME || currState == MenuStates::MULTI_GAME) {
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
                {
                    auto entity_guard = std::lock_guard(*entityPtr.get());
                    actions.pop();
                }
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
                ShootingFrequency &freq = entityPtr.get()->getComponent<ShootingFrequency>();
                const char hex_char[] = "0123456789ABCDEF";
                RandomDevice &random = world.getResource<RandomDevice>();
                std::string uuid(16, '\0');

                if (freq.frequency == duration<double>(0.0)) {
                    {
                        auto guard = std::lock_guard(random);
                        for (auto &c : uuid) {
                            c = hex_char[random.randInt<int>(0, 15)];
                        }
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
        std::vector<std::shared_ptr<Entity>> player = world.joinEntities<Controlable>();
        double moveD = double(move);

        if (player.empty())
            return;
        auto moveX = [moveD](std::shared_ptr<Entity> entityPtr) {
            auto guard = std::lock_guard(*entityPtr.get());
            if (!entityPtr->contains<InputDelayComponent>())
                entityPtr->addComponent<InputDelayComponent>(
                    moveD, entityPtr->getComponent<Velocity>().multiplierOrdinate);
            else
                entityPtr->getComponent<graphicECS::SFML::Components::InputDelayComponent>().multiplierAbscissa = moveD;

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
            auto guard = std::lock_guard(*entityPtr.get());
            if (!entityPtr->contains<InputDelayComponent>())
                entityPtr->addComponent<InputDelayComponent>(
                    entityPtr->getComponent<Velocity>().multiplierAbscissa, moveD);
            else
                entityPtr->getComponent<graphicECS::SFML::Components::InputDelayComponent>().multiplierOrdinate = moveD;
            entityPtr->getComponent<Velocity>().modified = true;
            entityPtr->getComponent<Position>().modified = true;
        };
        std::for_each(player.begin(), player.end(), moveY);
    }

    void InputManagement::shootAction(World &world, float action)
    {
        std::vector<std::shared_ptr<Entity>> player = world.joinEntities<Controlable>();

        if (player.empty())
            return;
        for (std::shared_ptr<ecs::Entity> p : player) {
            if (action > 1 && !(p->contains<IsShootingComponent>())) {
                std::lock_guard(*p.get());
                p->addComponent<IsShootingComponent>();
            } else if (action < 1 && p->contains<IsShootingComponent>()) {
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
        bool actionRealised = false;

        auto clickInButton = [this, &world, &mousePos, &actionRealised](std::shared_ptr<Entity> entityPtr) {
            Position &pos = entityPtr.get()->getComponent<Position>();
            Size &size = entityPtr.get()->getComponent<Size>();
            DisplayState &state = entityPtr.get()->getComponent<DisplayState>();

            bool sameWidth = pos.y <= mousePos.y && mousePos.y <= pos.y + size.y;
            bool sameHeigth = pos.x <= mousePos.x && mousePos.x <= pos.x + size.x;
            MenuStates &menuState = world.getResource<MenuStates>();
            MenuStates::menuState_e currState = menuState.currentState;
            if (!actionRealised && sameHeigth && sameWidth && state.displayState == currState) {
                entityPtr->getComponent<Button>().IsClicked = true;
                ActionName &name = entityPtr.get()->getComponent<ActionName>();
                ButtonActionMap &map = world.getResource<ButtonActionMap>();

                std::function<void(World &, Entity &)> fct = map.actionList.find(name.actionName)->second;
                fct(world, *(entityPtr.get()));
                actionRealised = true;
            }
        };
        std::for_each(joined.begin(), joined.end(), clickInButton);
    }
} // namespace graphicECS::SFML::Systems
