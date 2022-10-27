/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** GraphicsTextComponentTests
*/

#include <criterion/criterion.h>
#include <GraphicsTextComponent.hpp>

using namespace ecs;
using namespace graphicECS::SFML::Components;

Test(GraphicsTextComponent, test_create_function)
{
    GraphicsTextComponent a("text", 100, 100, 32);

    cr_assert_eq(a.text.getString(), std::string("text"));
    cr_assert_eq(a.text.getCharacterSize(), 32);
    cr_assert_eq(a.text.getPosition(), sf::Vector2f(100, 100));
}