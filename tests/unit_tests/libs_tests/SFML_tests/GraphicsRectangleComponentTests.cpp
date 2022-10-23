/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** GraphicsRectangleComponentTests
*/

#include <criterion/criterion.h>
#include "GraphicECS/SFML/Components/GraphicsRectangleComponent.hpp"

using namespace ecs;
using namespace graphic::sfml;

Test(GraphicsRectangleComponent, test_create_class)
{
    GraphicsRectangleComponent a(100, 100, 10, 10);

    cr_assert_eq(a.shape.getPosition(), sf::Vector2f(100, 100));
    cr_assert_eq(a.shape.getSize(), sf::Vector2f(10, 10));
}
