/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** KeyboardInputComponentTests
*/

#include <criterion/criterion.h>
#include "KeyboardInputComponent.hpp"
#include "SFML/Graphics.hpp"

using namespace ecs;

Test(KeyboardInputComponent, test_create_class)
{
    KeyboardInputComponent a;

    a.keyboardMapActions[sf::Keyboard::A] = std::pair<action_e, float>(action_e::NONE, 1);
    cr_assert_eq(a.keyboardMapActions[sf::Keyboard::A].first, NONE);
    cr_assert_eq(a.keyboardMapActions[sf::Keyboard::A].second, 1);
}

Test(KeyboardInputComponent, test_find_key_true)
{
    KeyboardInputComponent a;

    a.keyboardMapActions[sf::Keyboard::A] = std::pair<action_e, float>(action_e::NONE, 1);
    cr_assert_eq(a.keyboardMapActions.contains(sf::Keyboard::A), true);
}

Test(KeyboardInputComponent, test_find_key_false)
{
    KeyboardInputComponent a;

    a.keyboardMapActions[sf::Keyboard::A] = std::pair<action_e, float>(action_e::NONE, 1);
    cr_assert_eq(a.keyboardMapActions.contains(sf::Keyboard::B), false);
}