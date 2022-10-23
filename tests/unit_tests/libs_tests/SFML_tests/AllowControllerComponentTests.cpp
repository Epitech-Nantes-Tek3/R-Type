/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** AllowControllerComponentTests
*/

#include <criterion/criterion.h>
#include "GraphicECS/SFML/Components/AllowControllerComponent.hpp"

using namespace ecs;
using namespace graphic::sfml;

Test(AllowControllerComponent, test_class_constructor)
{
    AllowControllerComponent a;
    (void)a;
    cr_assert_eq(42, 42);
}
