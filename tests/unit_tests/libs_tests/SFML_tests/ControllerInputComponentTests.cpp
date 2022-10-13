/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** ControllerInputComponentTests
*/

#include <criterion/criterion.h>
#include "ControllerJoystickInputComponent.hpp"
#include "ControllerButtonInputComponent.hpp"

using namespace ecs;

static void test_function() {}

Test(ControllerJoystickInputComponent, test_create_class)
{
    ControllerJoystickInputComponent a;
    auto b = std::bind(&test_function);

    a.controllerJoystickMapActions[0] = std::pair<std::function<void()>, float>(b, 1);
    a.controllerJoystickMapActions[0].first();
    cr_assert_eq(a.controllerJoystickMapActions[0].second, 1);
}

Test(ControllerButtonInputComponent, test_create_class2)
{
    ControllerButtonInputComponent a;
    auto b = std::bind(&test_function);

    a.controllerButtonMapActions[0] = std::pair<std::function<void()>, float>(b, 1);
    a.controllerButtonMapActions[0].first();
    cr_assert_eq(a.controllerButtonMapActions[0].second, 1);
}