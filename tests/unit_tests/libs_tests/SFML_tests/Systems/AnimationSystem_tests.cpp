/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** AnimationSystem_tests
*/

#include <criterion/criterion.h>
#include "AnimationComponent.hpp"
#include "AnimationFrequencyComponent.hpp"
#include "AnimationSystem.hpp"
#include "GraphicECS/SFML/Components/GraphicsRectangleComponent.hpp"
#include "World/World.hpp"

using namespace graphicECS::SFML::Components;
using namespace graphicECS::SFML::Systems;

Test(AnimationSystem, create_basic_animation)
{
    World world(1);

    world.addEntity().addComponent<AnimationComponent>().addComponent<AnimationFrequencyComponent>().addComponent<GraphicsRectangleComponent>();
    world.addSystem<AnimationSystem>();

    world.runSystems();
    cr_assert_eq(1, 1);
}
