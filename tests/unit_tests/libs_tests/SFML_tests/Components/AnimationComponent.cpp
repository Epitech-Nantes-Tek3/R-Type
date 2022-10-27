/*
** EPITECH PROJECT, 2022
** R-Type [WSL : Ubuntu]
** File description:
** AnimationComponent
*/

#include <criterion/criterion.h>
#include "AnimationComponent.hpp"

Test(AnimationComponent, create_class)
{
    ecs::AnimationComponent a;

    cr_assert_eq(1, 1);
}
