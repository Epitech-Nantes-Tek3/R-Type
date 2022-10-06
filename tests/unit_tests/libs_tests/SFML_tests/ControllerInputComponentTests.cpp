/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** ControllerInputComponentTests
*/

#include <criterion/criterion.h>
#include "ControllerInputComponent.hpp"

using namespace ecs;

Test(ControllerInputComponent, test_create_class)
{
    ControllerInputComponent a;

    a.controllerMapActions[a.BUTTON_1] = std::pair<action_e, float>(NONE, 1);
    cr_assert_eq(a.controllerMapActions.at(a.BUTTON_1).first, NONE);
    cr_assert_eq(a.controllerMapActions.at(a.BUTTON_1).second, 1);
}