/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** CreateButton_tests
*/

#include <criterion/criterion.h>
#include "World/World.hpp"
#include "R-TypeLogic/EntityManipulation/ButtonManipulation/Components/DisplayState.hpp"
#include "R-TypeLogic/EntityManipulation/ButtonManipulation/Components/ActionName.hpp"
#include "R-TypeLogic/EntityManipulation/CreateEntitiesFunctions/CreateButton.hpp"
#include "R-TypeLogic/Global/Components/LayerLvL.hpp"
#include "R-TypeLogic/Global/Components/PositionComponent.hpp"
#include "R-TypeLogic/Global/Components/SizeComponent.hpp"

using namespace ecs;

Test(CreateButton_test, CreateButton)
{
    World world(1);

    std::size_t id_new_entity =
        createNewButton(world, 10, 10, 1, 10, ButtonActionMap::UNDEFINED, LayerLvL::BUTTON, MenuStates::UNDEFINED, "test");

    cr_assert_eq(1, id_new_entity);

    Entity &entity = world.getEntity(id_new_entity);
    Position &pos = entity.getComponent<Position>();
    Size &size = entity.getComponent<Size>();
    LayerLvL &level = entity.getComponent<LayerLvL>();
    ActionName &name = entity.getComponent<ActionName>();
    DisplayState &state = entity.getComponent<DisplayState>();

    cr_assert_eq(10, pos.x);
    cr_assert_eq(10, pos.y);
    cr_assert_eq(1, size.x);
    cr_assert_eq(10, size.y);
    cr_assert_eq(level.layer, LayerLvL::BUTTON);
    cr_assert_eq(name.actionName, ButtonActionMap::UNDEFINED);
    cr_assert_eq(state.displayState, MenuStates::UNDEFINED);
}
