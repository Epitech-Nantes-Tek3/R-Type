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

Test(MouseInputComponent, test_create_class)
{
    MouseInputComponent a;

    a.MouseMapActions[sf::Mouse::Button::Left] = std::pair<action_e, float>(NONE, 1);
    cr_assert_eq(a.MouseMapActions.at(sf::Mouse::Button::Left).first, NONE);
    cr_assert_eq(a.MouseMapActions.at(sf::Mouse::Button::Left).second, 1);
}

Test(MouseInputComponent, test_find_key_true)
{
    MouseInputComponent a;

    a.MouseMapActions[sf::Mouse::Button::Left] = std::pair<action_e, float>(NONE, 1);
    cr_assert_eq(a.MouseMapActions.contains(sf::Mouse::Button::Left), true);
}

Test(MouseInputComponent, test_find_key_false)
{
    MouseInputComponent a;

    a.MouseMapActions[sf::Mouse::Button::Left] = std::pair<action_e, float>(NONE, 1);
    cr_assert_eq(a.MouseMapActions.contains(sf::Mouse::Button::Right), false);
}