/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** Death_Life_System_tests
*/

#include <criterion/criterion.h>
#include "Entity/Entity.hpp"
#include "World/World.hpp"
#include "R-TypeLogic/Components/DeathComponent.hpp"
#include "R-TypeLogic/Components/LifeComponent.hpp"
#include "R-TypeLogic/Components/ProjectileComponent.hpp"
#include "R-TypeLogic/EntityManipulation/CreateEntitiesFunctions/CreateProjectile.hpp"
#include "R-TypeLogic/Systems/DeathLifeSystem.hpp"

using namespace ecs;

Test(add_Death_component_system, life_death_entity)
{
    World world(1);

    createNewProjectile(world, 10, 10, 1, 1, 10);

    world.getEntity(1).getComponent<Life>().lifePoint = 0;

    std::vector<std::shared_ptr<ecs::Entity>> joined = world.joinEntities<Death>();

    world.addSystem<DeathLife>();

    world.runSystems();

    std::vector<std::shared_ptr<ecs::Entity>> death_joined = world.joinEntities<Death>();

    cr_assert_eq(0, joined.size());
    cr_assert_eq(1, death_joined.size());
}

Test(add_Death_component_system, life_death_entities)
{
    World world(1);

    createNewProjectile(world, 10, 10, 1, 1, 10);
    createNewProjectile(world, 10, 10, 1, 1, 10);
    createNewProjectile(world, 10, 10, 1, 1, 10);

    world.getEntity(1).getComponent<Life>().lifePoint = 1;
    world.getEntity(2).getComponent<Life>().lifePoint = 0;
    world.getEntity(3).getComponent<Life>().lifePoint = 0;

    std::vector<std::shared_ptr<ecs::Entity>> joined = world.joinEntities<Death>();

    world.addSystem<DeathLife>();

    world.runSystems();

    std::vector<std::shared_ptr<ecs::Entity>> death_joined = world.joinEntities<Death>();

    cr_assert_eq(0, joined.size());
    cr_assert_eq(2, death_joined.size());
}
