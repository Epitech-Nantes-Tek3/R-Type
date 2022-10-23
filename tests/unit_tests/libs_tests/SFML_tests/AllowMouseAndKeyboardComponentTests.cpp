/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** AllowMouseAndKeyboardComponentTests
*/

#include <criterion/criterion.h>
#include "GraphicECS/SFML/Components/AllowMouseAndKeyboardComponent.hpp"

using namespace ecs;
using namespace graphic::sfml;

Test(AllowMouseAndKeyboardComponent, test_class_constructor)
{
    AllowMouseAndKeyboardComponent a;
    (void)a;
    cr_assert_eq(42, 42);
}
