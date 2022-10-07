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

static void test_function() {}

Test(KeyboardInputComponent, test_create_class)
{
    KeyboardInputComponent a;
    auto b = std::bind(&test_function);

    a.keyboardMapActions[sf::Keyboard::A] = std::pair<std::function<void()>, float>(b, 1);
    a.keyboardMapActions[sf::Keyboard::A].first();
    cr_assert_eq(a.keyboardMapActions[sf::Keyboard::A].second, 1);
}

Test(KeyboardInputComponent, test_find_key_true)
{
    KeyboardInputComponent a;
    auto b = std::bind(&test_function);

    a.keyboardMapActions[sf::Keyboard::A] = std::pair<std::function<void()>, float>(b, 1);
    a.keyboardMapActions[sf::Keyboard::A].first();
    cr_assert_eq(a.keyboardMapActions.contains(sf::Keyboard::A), true);
}

Test(KeyboardInputComponent, test_find_key_false)
{
    KeyboardInputComponent a;
    auto b = std::bind(&test_function);

    a.keyboardMapActions[sf::Keyboard::A] = std::pair<std::function<void()>, float>(b, 1);
    a.keyboardMapActions[sf::Keyboard::A].first();
    cr_assert_eq(a.keyboardMapActions.contains(sf::Keyboard::B), false);
}