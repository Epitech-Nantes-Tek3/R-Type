/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** InputManagement
*/

#include "InputManagement.hpp"
#include "World/World.hpp"
#include "RenderWindowResource.hpp"
#include "MouseInputComponent.hpp"
#include "KeyboardInputComponent.hpp"
#include "ControllerJoystickInputComponent.hpp"
#include "ControllerButtonInputComponent.hpp"
#include "ActionQueueComponent.hpp"

using namespace ecs;

void InputManagement::run(World &world)
{
    sf::Event event;
    std::vector<std::shared_ptr<Entity>> Inputs = world.joinEntities<MouseInputComponent, KeyboardInputComponent, ControllerButtonInputComponent, ControllerJoystickInputComponent, ActionQueueComponent>();

    while (world.getResource<RenderWindowResource>().window.pollEvent(event)) {
        switch (event.type)
        {
        case sf::Event::KeyPressed:
            auto keyPressed = [event](std::shared_ptr<ecs::Entity> entityPtr) {
                if (entityPtr->getComponent<KeyboardInputComponent>().keyboardMapActions.contains(event.key.code))
                    entityPtr->getComponent<ActionQueueComponent>().actions.push(entityPtr->getComponent<KeyboardInputComponent>().keyboardMapActions[event.key.code].first);
            };
            std::for_each(Inputs.begin(), Inputs.end(), keyPressed);
            break;
        case sf::Event::MouseButtonPressed:
            auto mouseButtonPressed = [event](std::shared_ptr<ecs::Entity> entityPtr) {
                if (entityPtr->getComponent<MouseInputComponent>().MouseMapActions.contains(event.mouseButton.button))
                    entityPtr->getComponent<ActionQueueComponent>().actions.push(entityPtr->getComponent<MouseInputComponent>().MouseMapActions[event.mouseButton.button].first);
            };
            std::for_each(Inputs.begin(), Inputs.end(), mouseButtonPressed);
            break;
        case sf::Event::JoystickButtonPressed:
            auto joyButtonPressed = [event](std::shared_ptr<ecs::Entity> entityPtr) {
                if (entityPtr->getComponent<ControllerButtonInputComponent>().controllerButtonMapActions.contains(event.joystickButton.button))
                    entityPtr->getComponent<ActionQueueComponent>().actions.push(entityPtr->getComponent<ControllerButtonInputComponent>().controllerButtonMapActions[event.joystickButton.button].first);
            };
            std::for_each(Inputs.begin(), Inputs.end(), joyButtonPressed);
            break;
        case sf::Event::JoystickMoved:
            auto joyMovePressed = [event](std::shared_ptr<ecs::Entity> entityPtr) {
                if (entityPtr->getComponent<ControllerJoystickInputComponent>().controllerJoystickMapActions.contains(event.joystickMove.axis))
                    entityPtr->getComponent<ActionQueueComponent>().actions.push(entityPtr->getComponent<ControllerJoystickInputComponent>().controllerJoystickMapActions[event.joystickMove.axis].first);
            };
            std::for_each(Inputs.begin(), Inputs.end(), joyMovePressed);
            break;
        default:
            break;
        }
    }
}