/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** GraphicsTextComponentTests
*/

#include <GraphicsTextComponent.hpp>
#include <SFML/Graphics.hpp>
#include <filesystem>
#include <criterion/criterion.h>

using namespace ecs;
using namespace graphicECS::SFML::Components;

Test(GraphicsTextComponent, test_create_function)
{
    sf::Font font;
    font.loadFromFile(std::filesystem::path("arial.ttf"));
    GraphicsTextComponent a(font, "text", 100, 100, 32);

    cr_assert_eq(a.text.getString(), std::string("text"));
    cr_assert_eq(a.text.getCharacterSize(), 32);
    cr_assert_eq(a.text.getPosition(), sf::Vector2f(100, 100));
}