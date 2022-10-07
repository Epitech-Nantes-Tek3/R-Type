/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** MouseInputComponentTests
*/

#include <criterion/criterion.h>
#include "MouseInputComponent.hpp"
#include "SFML/Graphics.hpp"

using namespace ecs;

static void test_function() {}

Test(MouseInputComponent, test_create_class)
{
    MouseInputComponent a;
    auto b = std::bind(&test_function);

    a.MouseMapActions[sf::Mouse::Button::Left] = std::pair<std::function<void()>, float>(b, 1);
    a.MouseMapActions[sf::Mouse::Button::Left].first();
    cr_assert_eq(a.MouseMapActions.at(sf::Mouse::Button::Left).second, 1);
}

Test(MouseInputComponent, test_find_key_true)
{
    MouseInputComponent a;
    auto b = std::bind(&test_function);

    a.MouseMapActions[sf::Mouse::Button::Left] = std::pair<std::function<void()>, float>(b, 1);
    a.MouseMapActions[sf::Mouse::Button::Left].first();
    cr_assert_eq(a.MouseMapActions.contains(sf::Mouse::Button::Left), true);
}

Test(MouseInputComponent, test_find_key_false)
{
    MouseInputComponent a;
    auto b = std::bind(&test_function);

    a.MouseMapActions[sf::Mouse::Button::Left] = std::pair<std::function<void()>, float>(b, 1);
    a.MouseMapActions[sf::Mouse::Button::Left].first();
    cr_assert_eq(a.MouseMapActions.contains(sf::Mouse::Button::Right), false);
}