/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** InputManagement_tests
*/

#include <criterion/criterion.h>
#include "ActionQueueComponent.hpp"
#include "AllowControllerComponent.hpp"
#include "AllowMouseAndKeyboardComponent.hpp"
#include "ControllerButtonInputComponent.hpp"
#include "ControllerJoystickInputComponent.hpp"
#include "GraphicECS/SFML/Resources/RenderWindowResource.hpp"
#include "KeyboardInputComponent.hpp"
#include "MouseInputComponent.hpp"
#include "R-TypeLogic/Global/SharedResources/GameClock.hpp"
#define private public
#include "InputManagement.hpp"

Test(InputManagement, create_system)
{
    InputManagement inputs;

    cr_assert_eq(1, 1);
}

Test(InputManagement, run_system_without_input_entity)
{
    InputManagement inputs;
    World world(1);

    inputs.run(world);
    cr_assert_eq(1, 1);
}

Test(InputManagement, movePlayerX_without_player)
{
    InputManagement inputs;
    World world(1);

    inputs.movePlayerX(world, 1);
    cr_assert_eq(1, 1);
}

Test(InputManagement, movePlayerX_with_player)
{
    InputManagement inputs;
    World world(1);
    Entity::ID id =
        world.addEntity().addComponent<Controlable>().addComponent<Velocity>(0, 0).addComponent<Position>(0, 0).getId();

    inputs.movePlayerX(world, 10);
    cr_assert_eq(world.getEntity(id).getComponent<Velocity>().multiplierAbscissa, 10);
}

Test(InputManagement, movePlayerY_without_player)
{
    InputManagement inputs;
    World world(1);

    inputs.movePlayerY(world, 1);
    cr_assert_eq(1, 1);
}

Test(InputManagement, movePlayerY_with_player)
{
    InputManagement inputs;
    World world(1);
    Entity::ID id =
        world.addEntity().addComponent<Controlable>().addComponent<Velocity>(0, 0).addComponent<Position>(0, 0).getId();

    inputs.movePlayerY(world, 10);
    cr_assert_eq(world.getEntity(id).getComponent<Velocity>().multiplierOrdinate, 10);
}

Test(InputManagement, keyPressedEvents)
{
    InputManagement inputs;
    sf::Event event;
    World world(1);
    world.addEntity().addComponent<Controlable>().addComponent<Velocity>(0, 0).addComponent<Position>(0, 0).getId();
    world.addEntity().addComponent<MouseInputComponent>().addComponent<KeyboardInputComponent>().addComponent<ControllerButtonInputComponent>().addComponent<ControllerJoystickInputComponent>().addComponent<ActionQueueComponent>().addComponent<AllowMouseAndKeyboardComponent>();
    std::vector<std::shared_ptr<Entity>> Inputs = world.joinEntities<MouseInputComponent, KeyboardInputComponent,
        ControllerButtonInputComponent, ControllerJoystickInputComponent, ActionQueueComponent>();

    Inputs[0]->getComponent<KeyboardInputComponent>().keyboardMapActions.emplace(
        std::make_pair<sf::Keyboard::Key, std::pair<ActionQueueComponent::inputAction_e, float>>(sf::Keyboard::Z,
            std::make_pair<ActionQueueComponent::inputAction_e, float>(ActionQueueComponent::MOVEY, -200)));
    event.type = sf::Event::KeyPressed;
    event.key.code = sf::Keyboard::Z;
    inputs._keyPressedEvents(event, Inputs);
    cr_assert_eq(Inputs[0]->getComponent<ActionQueueComponent>().actions.size(), 1);
    cr_assert_eq(Inputs[0]->getComponent<ActionQueueComponent>().actions.back().first, ActionQueueComponent::MOVEY);
    cr_assert_eq(Inputs[0]->getComponent<ActionQueueComponent>().actions.back().second, -200);
}

Test(InputManagement, keyReleasedEvents)
{
    InputManagement inputs;
    sf::Event event;
    World world(1);
    world.addEntity().addComponent<Controlable>().addComponent<Velocity>(0, 0).addComponent<Position>(0, 0).getId();
    world.addEntity().addComponent<MouseInputComponent>().addComponent<KeyboardInputComponent>().addComponent<ControllerButtonInputComponent>().addComponent<ControllerJoystickInputComponent>().addComponent<ActionQueueComponent>().addComponent<AllowMouseAndKeyboardComponent>();
    std::vector<std::shared_ptr<Entity>> Inputs = world.joinEntities<MouseInputComponent, KeyboardInputComponent,
        ControllerButtonInputComponent, ControllerJoystickInputComponent, ActionQueueComponent>();

    Inputs[0]->getComponent<KeyboardInputComponent>().keyboardMapActions.emplace(
        std::make_pair<sf::Keyboard::Key, std::pair<ActionQueueComponent::inputAction_e, float>>(sf::Keyboard::Z,
            std::make_pair<ActionQueueComponent::inputAction_e, float>(ActionQueueComponent::MOVEY, -200)));
    event.type = sf::Event::KeyReleased;
    event.key.code = sf::Keyboard::Z;
    inputs._keyReleasedEvents(event, Inputs);
    cr_assert_eq(Inputs[0]->getComponent<ActionQueueComponent>().actions.size(), 1);
    cr_assert_eq(Inputs[0]->getComponent<ActionQueueComponent>().actions.back().first, ActionQueueComponent::MOVEY);
    cr_assert_eq(Inputs[0]->getComponent<ActionQueueComponent>().actions.back().second, -200);
}

Test(InputManagement, actionsLists)
{
    InputManagement inputs;
    World world(1);
    world.addEntity().addComponent<MouseInputComponent>().addComponent<KeyboardInputComponent>().addComponent<ControllerButtonInputComponent>().addComponent<ControllerJoystickInputComponent>().addComponent<ActionQueueComponent>().addComponent<AllowMouseAndKeyboardComponent>();
    std::vector<std::shared_ptr<Entity>> Inputs = world.joinEntities<MouseInputComponent, KeyboardInputComponent,
        ControllerButtonInputComponent, ControllerJoystickInputComponent, ActionQueueComponent>();
    Inputs[0]->getComponent<ActionQueueComponent>().actions.push(std::make_pair<ActionQueueComponent::inputAction_e, float>(ActionQueueComponent::MOVEX, 100));
    Inputs[0]->getComponent<ActionQueueComponent>().actions.push(std::make_pair<ActionQueueComponent::inputAction_e, float>(ActionQueueComponent::MOVEY, 100));
    Inputs[0]->getComponent<ActionQueueComponent>().actions.push(std::make_pair<ActionQueueComponent::inputAction_e, float>(ActionQueueComponent::SHOOT, 0));
    cr_assert_eq(Inputs[0]->getComponent<ActionQueueComponent>().actions.size(), 3);
    inputs.run(world);
    cr_assert_eq(Inputs[0]->getComponent<ActionQueueComponent>().actions.size(), 0);
}
